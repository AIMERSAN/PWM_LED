#ifndef __CH395SPI_H_
#define __CH395SPI_H_

#include "CH395INC.H"
#include "stm32f4xx.h"

/*******************************配置GPIO (根据自己的修改)****************************************/
//时钟
#define CH395_CONFIG_SPI_CLK()   ( RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1, ENABLE) )
#define CH395_CONFIG_GPIO_CLK()  ( RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE ) )

//设置使用SPI1
#define USE_SPI SPI1

/*
    CH395引脚分配:
    NSS--->PA4 或 PA15
    SCK--->PA5 或 PB3
    MISO--->PA6 或 PB4
    MOSI--->PA7 或 PB5
    RST--->PC4
    INT--->PC5
*/


//SPI_CS  --  连接模块SCS引脚
#define CH395_CS_PORT    GPIOA
#define CH395_CS_PIN     GPIO_Pin_15

//SPI_CLK --  连接模块SCK引脚 PA5 或 PB3
#define CH395_CLK_PORT   GPIOB
#define CH395_CLK_PIN    GPIO_Pin_3

//SPI_MISO -- 连接模块SDO引脚 PA6或PB4
#define CH395_MISO_PORT  GPIOB
#define CH395_MISO_PIN   GPIO_Pin_4

//SPI_MOSI -- 连接模块SDI引脚
#define CH395_MOSI_PORT  GPIOB
#define CH395_MOSI_PIN   GPIO_Pin_5

//RST --  连接模块RST引脚
#define CH395_RST_PORT  GPIOC
#define CH395_RST_PIN   GPIO_Pin_4

//INT  -- 连接模块INT引脚 (检测到中断信号之后再获取数据)
#define CH395_INT_PORT  GPIOC
#define CH395_INT_PIN   GPIO_Pin_5

/***********************************************************************/
#define CH395_SPI_CS_LOW()     ( CH395_CS_PORT->BSRR = (( CH395_CS_PIN ) << 16 ) )    /*CS输出低*/
#define CH395_SPI_CS_HIGH()    ( CH395_CS_PORT->BSRR = CH395_CS_PIN )                 /*CS输出高*/

#define CH395_RST_PIN_LOW()    ( CH395_RST_PORT->BSRR = ( ( CH395_RST_PIN ) << 16 ) ) /*RST输出高*/
#define CH395_RST_PIN_HIGH()   ( CH395_RST_PORT->BSRR = CH395_RST_PIN )               /*RST输出低*/

#define CH395_INT_PIN_INPUT()  ( CH395_INT_PORT->IDR & CH395_INT_PIN )                /* 获取INT电平 */   

/*******************************************************************************
* Function Name  : Delay_uS
* Description    : 微秒级延时函数(基本准确)
* Input          : delay---延时值
* Output         : None
* Return         : None
*******************************************************************************/
void mDelayuS( UINT8 delay );

/*******************************************************************************
* Function Name  : Delay_mS
* Description    : 毫秒级延时函数(基本准确)
* Input          : delay---延时值
* Output         : None
* Return         : None
*******************************************************************************/
void mDelaymS( UINT8 delay );


/*******************************************************************************
* Function Name  : CH395_Port_Init
* Description    : CH395端口初始化
*                  由于使用SPI读写时序,所以进行初始化
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_PORT_INIT( void );

UINT8 Spi395Exchange( UINT8 d );
/*******************************************************************************
* Function Name  : xWriteCH395Cmd
* Description    : 向CH395写命令
* Input          : mCmd---将要写入CH395的命令码
* Output         : None
* Return         : None
*******************************************************************************/
void xWriteCH395Cmd( UINT8 mCmd );



/*******************************************************************************
* Function Name  : xWriteCH395Data
* Description    : 向CH395写数据
* Input          : mData---将要写入CH395的数据
* Output         : None
* Return         : None
*******************************************************************************/
void xWriteCH395Data( UINT8 mData );

/*******************************************************************************
* Function Name  : xReadCH395Data
* Description    : 从CH395读数据
* Input          : None
* Output         : None
* Return         : 返回读取的数据
*******************************************************************************/
UINT8 xReadCH395Data( void );

/*******************************************************************************
* Function Name  : CH395_RST
* Description    : 复位 CH395
* Input          : None
* Output         : None
* Return         : 返回中断状态
*******************************************************************************/
void CH395_RST( void );

UINT8 Query395Interrupt( void );

#endif
