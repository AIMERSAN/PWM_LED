/**
  ******************************************************************************
  * @file    usart1.c
  * @author  yuan hang
  * @version V1.0.0
  * @date    2023/06/11
  * @brief   usart1 driver file
  ******************************************************************************/


#include "usart1.h"

/*	定义16位接收状态寄存器，
	bit15置1接收完成，
	bit14置1表示接收到0x0D标志，
	bit13～0表示接收到的有效数据个数
	*/
uint16_t USART_RX_STA;

//接收缓存数组,最大USART_REC_LEN个字节
u8 receive_str[UART_REC_NUM];

/****************************************************************************
* 名    称: void uart_init(u32 bound)
* 功    能：USART1初始化
* 入口参数：bound：波特率
* 返回参数：无
* 说    明：
****************************************************************************/
void uart_init( u32 bound )
{   
	//GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd( USART_TX_CLK | USART_RX_CLK, ENABLE);
    RCC_APB1PeriphClockCmd( USART_CLK, ENABLE );//使能UART时钟
	
    //串口对应引脚复用映射
    GPIO_PinAFConfig( USART_TX_PORT, USART_TX_Source, USART_TX_AF );
    GPIO_PinAFConfig( USART_RX_PORT, USART_RX_Source, USART_RX_AF );
	
    //USART端口配置
    GPIO_InitStructure.GPIO_Pin = USART_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init( USART_TX_PORT, &GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = USART_RX_PIN;
    GPIO_Init( USART_RX_PORT, &GPIO_InitStructure );

    //UART5 初始化设置
    USART_InitStructure.USART_BaudRate   = bound;                           //波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;             //字长为8位数据格式
    USART_InitStructure.USART_StopBits   = USART_StopBits_1;                //一个停止位
    USART_InitStructure.USART_Parity     = USART_Parity_No;                 //无奇偶校验位
    USART_InitStructure.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;   //收发模式
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_Init( UART_USE, &USART_InitStructure );
    USART_Cmd( UART_USE, ENABLE );

    USART_ClearFlag( UART_USE, USART_FLAG_TC);

    USART_ITConfig( UART_USE, USART_IT_RXNE, ENABLE);         //开启相关中断
	
    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel                   = UART_Irqn; //串口中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;         //抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;		  //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;	  //IRQ通道使能
    NVIC_Init( &NVIC_InitStructure );	                                  //根据指定的参数初始化VIC寄存器、
}

//串口发送一个字符
void uartSendChar( u8 ch )
{
    while(( UART_USE->SR & 0x40 ) == 0 )
    {
    }
    UART_USE->DR = ( u8 ) ch;
}

/****************************************************************************
* 名    称: int fputc(int ch, FILE *f)
* 功    能：重定向，让printf输出到串口
* 入口参数：
* 返回参数：
* 说    明：因printf()之类的函数，使用了半主机模式。使用标准库会导致程序无法
            运行,以下是解决方法:使用微库,因为使用微库的话,不会使用半主机模式.
            请在工程属性的“Target“-》”Code Generation“中勾选”Use MicroLIB“这
            样以后就可以使用printf，sprintf函数了
****************************************************************************/
int fputc( int ch, FILE *f )   //重定向，让printf输出到串口
{
    uartSendChar( ch );
    while (USART_GetFlagStatus( UART_USE, USART_FLAG_TC ) == RESET );
    return ch;
}

/****************************************************************************
* 名    称: void uartSendChars(u8 *str, u16 strlen)
* 功    能：串口发送一字符串
* 入口参数：*str：发送的字符串
            strlen：字符串长度
* 返回参数：无
* 说    明：
****************************************************************************/
void uartSendChars( u8 *str, u16 strlen )
{
    u16 k = 0;
    do
    {
        uartSendChar( *( str + k ) );
        k++;
    }//循环发送,直到发送完毕
    while ( k < strlen );
}

//串口中断服务程序
void UART_IRQHandler(void)
{
	uint8_t rec_data;
	
	if(USART_GetITStatus( UART_USE, USART_IT_RXNE ) != RESET)  //接收中断
	{
		rec_data = USART_ReceiveData( UART_USE );
		
		if( ( USART_RX_STA & 0x8000 ) == 0 ) //接收未完成
		{
			if( USART_RX_STA & 0x4000 ) //接收到了回车字符
			{
				if( rec_data != 0x0a ) //
				{
					USART_RX_STA = 0;
				}
				else
				{
					USART_RX_STA |= 0x8000;
				}
			}
		}
		else
		{
			if( rec_data == 0x0d )
			{
				USART_RX_STA |= 0x4000;
			}
			else
			{
				receive_str[USART_RX_STA & 0x3FFF] = rec_data;
				USART_RX_STA++;
				if( USART_RX_STA > ( UART_REC_NUM - 1 ) )
				{
					USART_RX_STA = 0;
				}
			}
		}
	}
}
