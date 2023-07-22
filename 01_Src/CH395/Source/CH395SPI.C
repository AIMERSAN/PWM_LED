/********************************** (C) COPYRIGHT *******************************
* File Name          : SPI_HW.C
* Author             : WXF
* Version            : V1.0
* Date               : 2013/12/19
* Description        : CH395芯片 CH395芯片 硬件标准SPI串行连接的硬件抽象层 V1.0
*                      提供I/O接口子程序
*******************************************************************************/
#include "CH395SPI.H"
#include "delay.h"
#include "CH395INC.H"

/*******************************************************************************
* Function Name  : Delay_uS
* Description    : 微秒级延时函数(基本准确)
* Input          : delay---延时值
* Output         : None
* Return         : None
*******************************************************************************/
void mDelayuS( UINT8 delay )
{
	//替换自己的延时us函数
	delay_us(delay);
}

/*******************************************************************************
* Function Name  : Delay_mS
* Description    : 毫秒级延时函数(基本准确)
* Input          : delay---延时值
* Output         : None
* Return         : None
*******************************************************************************/
void mDelaymS( UINT8 delay )
{
	//替换自己的延时ms函数
	delay_ms(delay);
}

/*******************************************************************************
* Function Name  : CH395_Port_Init
* Description    : CH395端口初始化
*                  由于使用SPI读写时序,所以进行初始化
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_PORT_INIT( void )  
{
	//替换自己的端口初始化函数
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* 初始化SPI接口 */
	CH395_CONFIG_SPI_CLK();
	CH395_CONFIG_GPIO_CLK();

	/* SCK引脚推挽输出功能 */
	GPIO_InitStructure.GPIO_Pin = CH395_CLK_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init( CH395_CLK_PORT, &GPIO_InitStructure );
	GPIO_PinAFConfig( CH395_CLK_PORT, GPIO_PinSource3, GPIO_AF_SPI1 );

	/* MISO引脚浮空输入功能 */
	GPIO_InitStructure.GPIO_Pin = CH395_MISO_PIN;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init( CH395_MISO_PORT, &GPIO_InitStructure );
	GPIO_PinAFConfig( CH395_MISO_PORT, GPIO_PinSource4, GPIO_AF_SPI1 );
	
	/* MOSI引脚推挽输出功能 */
	GPIO_InitStructure.GPIO_Pin = CH395_MOSI_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init( CH395_MOSI_PORT, &GPIO_InitStructure );
	GPIO_PinAFConfig( CH395_MOSI_PORT, GPIO_PinSource5, GPIO_AF_SPI1 );

	/* CS引脚推挽输出功能，低电平有效 */
	GPIO_InitStructure.GPIO_Pin = CH395_CS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init( CH395_CS_PORT, &GPIO_InitStructure );
	GPIO_PinAFConfig( CH395_MOSI_PORT, GPIO_PinSource15, GPIO_AF_SPI1 );
	
	/* RST引脚推挽输出功能，低电平有效 */
	GPIO_InitStructure.GPIO_Pin = CH395_RST_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 
	GPIO_Init( CH395_RST_PORT, &GPIO_InitStructure );

	/* 中断引脚初始化，上拉输入功能，低电平有效 */
	GPIO_InitStructure.GPIO_Pin = CH395_INT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init( CH395_INT_PORT, &GPIO_InitStructure );

	/* CS 引脚置为高 */
	//CH395_SPI_CS_HIGH();
	
	/* SPI configuration */ 
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; /* SPI配置成两线的单向全双工通信 */
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	 				   /* SPI主机 */
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;				   /* SPI8位数据格式传输 */
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;	  					   /* 空闲时时钟为低电平  */
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;					   /* 数据在时钟第一个边沿时捕获，时钟信号奇数沿采样 */
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		 				   /* 内部NSS信号由SSI控制 */
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; /* 波特率预分频数设置 */
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;		   		   /* 传输时高位在前 */
	SPI_InitStructure.SPI_CRCPolynomial = 7;			  			    
	SPI_Init( USE_SPI, &SPI_InitStructure );

	/* Enable SPI  */
	SPI_Cmd( USE_SPI, ENABLE );
}

/*******************************************************************************
* Function Name  : Spi395Exchange
* Description    : 硬件SPI输出且输入8个位数据
* Input          : d---将要送入到CH395的数据
* Output         : None
* Return         : SPI接收的数据
*******************************************************************************/
UINT8 Spi395Exchange( UINT8 d )  
{
    /* Loop while DR register in not emplty */
    while( SPI_I2S_GetFlagStatus( USE_SPI, SPI_I2S_FLAG_TXE ) == RESET );
    
    /* Send byte through the SPI1 peripheral */
    SPI_I2S_SendData( USE_SPI, d );
    
    /* Wait to receive a byte */
    while( SPI_I2S_GetFlagStatus( USE_SPI, SPI_I2S_FLAG_RXNE ) == RESET );
    
    /* Return the byte read from the SPI bus */
    SPI_I2S_ReceiveData( USE_SPI );
}

/*******************************************************************************
* Function Name  : xWriteCH395Cmd
* Description    : 向CH395写命令
* Input          : mCmd---将要写入CH395的命令码
* Output         : None
* Return         : None
*******************************************************************************/
void xWriteCH395Cmd( UINT8 mCmd )  
{
	//CH395_SPI_CS_HIGH();  									 /* 防止之前未通过xEndCH395Cmd禁止SPI片选 */
	CH395_SPI_CS_HIGH();
    mDelayuS( 1 );
	/* 对于双向I/O引脚模拟SPI接口,那么必须确保已经设置SPI_SCS,SPI_SCK,SPI_SDI为输出方向,SPI_SDO为输入方向 */
	CH395_SPI_CS_LOW();  								     /* SPI片选有效 */
    Spi395Exchange( mCmd );  							     /* 发出命令码 */
	mDelayuS( 10 );  									     /* 延时1.5uS确保读写周期大于1.5uS */
}

/*******************************************************************************
* Function Name  : xWriteCH395Data
* Description    : 向CH395写数据
* Input          : mData---将要写入CH395的数据
* Output         : None
* Return         : None
*******************************************************************************/
void xWriteCH395Data( UINT8 mData ) 
{
	Spi395Exchange( mData );  									/* 发送数据 */
}

/*******************************************************************************
* Function Name  : xReadCH395Data
* Description    : 从CH395读数据
* Input          : None
* Output         : None
* Return         : 返回读取的数据
*******************************************************************************/
UINT8 xReadCH395Data( void ) 
{
    while( ( USE_SPI->SR & SPI_I2S_FLAG_TXE ) == RESET );
    USE_SPI->DR = 0xFF;
    while( ( USE_SPI->SR & SPI_I2S_FLAG_RXNE ) == RESET );
    return (uint8_t) (USE_SPI->DR);
}

/*******************************************************************************
* Function Name  : Query395Interrupt
* Description    : 查询CH395中断(INT#低电平)
* Input          : None
* Output         : None
* Return         : 返回中断状态
*******************************************************************************/
UINT8 Query395Interrupt( void )
{
	return( CH395_INT_PIN_INPUT() ? FALSE : TRUE );  
}

/*******************************************************************************
* Function Name  : CH395_RST
* Description    : 复位 CH395
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_RST( void )
{
	CH395_RST_PIN_LOW();
	mDelaymS(10);
	CH395_RST_PIN_HIGH();
	mDelaymS(250);
}
