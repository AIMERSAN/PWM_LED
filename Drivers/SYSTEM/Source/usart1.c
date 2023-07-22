/**
  ******************************************************************************
  * @file    usart1.c
  * @author  yuan hang
  * @version V1.0.0
  * @date    2023/06/11
  * @brief   usart1 driver file
  ******************************************************************************/


#include "usart1.h"

/*	����16λ����״̬�Ĵ�����
	bit15��1������ɣ�
	bit14��1��ʾ���յ�0x0D��־��
	bit13��0��ʾ���յ�����Ч���ݸ���
	*/
uint16_t USART_RX_STA;

//���ջ�������,���USART_REC_LEN���ֽ�
u8 receive_str[UART_REC_NUM];

/****************************************************************************
* ��    ��: void uart_init(u32 bound)
* ��    �ܣ�USART1��ʼ��
* ��ڲ�����bound��������
* ���ز�������
* ˵    ����
****************************************************************************/
void uart_init( u32 bound )
{   
	//GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd( USART_TX_CLK | USART_RX_CLK, ENABLE);
    RCC_APB1PeriphClockCmd( USART_CLK, ENABLE );//ʹ��UARTʱ��
	
    //���ڶ�Ӧ���Ÿ���ӳ��
    GPIO_PinAFConfig( USART_TX_PORT, USART_TX_Source, USART_TX_AF );
    GPIO_PinAFConfig( USART_RX_PORT, USART_RX_Source, USART_RX_AF );
	
    //USART�˿�����
    GPIO_InitStructure.GPIO_Pin = USART_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init( USART_TX_PORT, &GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = USART_RX_PIN;
    GPIO_Init( USART_RX_PORT, &GPIO_InitStructure );

    //UART5 ��ʼ������
    USART_InitStructure.USART_BaudRate   = bound;                           //����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;             //�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits   = USART_StopBits_1;                //һ��ֹͣλ
    USART_InitStructure.USART_Parity     = USART_Parity_No;                 //����żУ��λ
    USART_InitStructure.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;   //�շ�ģʽ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_Init( UART_USE, &USART_InitStructure );
    USART_Cmd( UART_USE, ENABLE );

    USART_ClearFlag( UART_USE, USART_FLAG_TC);

    USART_ITConfig( UART_USE, USART_IT_RXNE, ENABLE);         //��������ж�
	
    //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel                   = UART_Irqn; //�����ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;         //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;		  //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;	  //IRQͨ��ʹ��
    NVIC_Init( &NVIC_InitStructure );	                                  //����ָ���Ĳ�����ʼ��VIC�Ĵ�����
}

//���ڷ���һ���ַ�
void uartSendChar( u8 ch )
{
    while(( UART_USE->SR & 0x40 ) == 0 )
    {
    }
    UART_USE->DR = ( u8 ) ch;
}

/****************************************************************************
* ��    ��: int fputc(int ch, FILE *f)
* ��    �ܣ��ض�����printf���������
* ��ڲ�����
* ���ز�����
* ˵    ������printf()֮��ĺ�����ʹ���˰�����ģʽ��ʹ�ñ�׼��ᵼ�³����޷�
            ����,�����ǽ������:ʹ��΢��,��Ϊʹ��΢��Ļ�,����ʹ�ð�����ģʽ.
            ���ڹ������Եġ�Target��-����Code Generation���й�ѡ��Use MicroLIB����
            ���Ժ�Ϳ���ʹ��printf��sprintf������
****************************************************************************/
int fputc( int ch, FILE *f )   //�ض�����printf���������
{
    uartSendChar( ch );
    while (USART_GetFlagStatus( UART_USE, USART_FLAG_TC ) == RESET );
    return ch;
}

/****************************************************************************
* ��    ��: void uartSendChars(u8 *str, u16 strlen)
* ��    �ܣ����ڷ���һ�ַ���
* ��ڲ�����*str�����͵��ַ���
            strlen���ַ�������
* ���ز�������
* ˵    ����
****************************************************************************/
void uartSendChars( u8 *str, u16 strlen )
{
    u16 k = 0;
    do
    {
        uartSendChar( *( str + k ) );
        k++;
    }//ѭ������,ֱ���������
    while ( k < strlen );
}

//�����жϷ������
void UART_IRQHandler(void)
{
	uint8_t rec_data;
	
	if(USART_GetITStatus( UART_USE, USART_IT_RXNE ) != RESET)  //�����ж�
	{
		rec_data = USART_ReceiveData( UART_USE );
		
		if( ( USART_RX_STA & 0x8000 ) == 0 ) //����δ���
		{
			if( USART_RX_STA & 0x4000 ) //���յ��˻س��ַ�
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
