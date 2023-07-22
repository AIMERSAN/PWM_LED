#ifndef __CH395SPI_H_
#define __CH395SPI_H_

#include "CH395INC.H"
#include "stm32f4xx.h"

/*******************************����GPIO (�����Լ����޸�)****************************************/
//ʱ��
#define CH395_CONFIG_SPI_CLK()   ( RCC_APB2PeriphClockCmd( RCC_APB2Periph_SPI1, ENABLE) )
#define CH395_CONFIG_GPIO_CLK()  ( RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE ) )

//����ʹ��SPI1
#define USE_SPI SPI1

/*
    CH395���ŷ���:
    NSS--->PA4 �� PA15
    SCK--->PA5 �� PB3
    MISO--->PA6 �� PB4
    MOSI--->PA7 �� PB5
    RST--->PC4
    INT--->PC5
*/


//SPI_CS  --  ����ģ��SCS����
#define CH395_CS_PORT    GPIOA
#define CH395_CS_PIN     GPIO_Pin_15

//SPI_CLK --  ����ģ��SCK���� PA5 �� PB3
#define CH395_CLK_PORT   GPIOB
#define CH395_CLK_PIN    GPIO_Pin_3

//SPI_MISO -- ����ģ��SDO���� PA6��PB4
#define CH395_MISO_PORT  GPIOB
#define CH395_MISO_PIN   GPIO_Pin_4

//SPI_MOSI -- ����ģ��SDI����
#define CH395_MOSI_PORT  GPIOB
#define CH395_MOSI_PIN   GPIO_Pin_5

//RST --  ����ģ��RST����
#define CH395_RST_PORT  GPIOC
#define CH395_RST_PIN   GPIO_Pin_4

//INT  -- ����ģ��INT���� (��⵽�ж��ź�֮���ٻ�ȡ����)
#define CH395_INT_PORT  GPIOC
#define CH395_INT_PIN   GPIO_Pin_5

/***********************************************************************/
#define CH395_SPI_CS_LOW()     ( CH395_CS_PORT->BSRR = (( CH395_CS_PIN ) << 16 ) )    /*CS�����*/
#define CH395_SPI_CS_HIGH()    ( CH395_CS_PORT->BSRR = CH395_CS_PIN )                 /*CS�����*/

#define CH395_RST_PIN_LOW()    ( CH395_RST_PORT->BSRR = ( ( CH395_RST_PIN ) << 16 ) ) /*RST�����*/
#define CH395_RST_PIN_HIGH()   ( CH395_RST_PORT->BSRR = CH395_RST_PIN )               /*RST�����*/

#define CH395_INT_PIN_INPUT()  ( CH395_INT_PORT->IDR & CH395_INT_PIN )                /* ��ȡINT��ƽ */   

/*******************************************************************************
* Function Name  : Delay_uS
* Description    : ΢�뼶��ʱ����(����׼ȷ)
* Input          : delay---��ʱֵ
* Output         : None
* Return         : None
*******************************************************************************/
void mDelayuS( UINT8 delay );

/*******************************************************************************
* Function Name  : Delay_mS
* Description    : ���뼶��ʱ����(����׼ȷ)
* Input          : delay---��ʱֵ
* Output         : None
* Return         : None
*******************************************************************************/
void mDelaymS( UINT8 delay );


/*******************************************************************************
* Function Name  : CH395_Port_Init
* Description    : CH395�˿ڳ�ʼ��
*                  ����ʹ��SPI��дʱ��,���Խ��г�ʼ��
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CH395_PORT_INIT( void );

UINT8 Spi395Exchange( UINT8 d );
/*******************************************************************************
* Function Name  : xWriteCH395Cmd
* Description    : ��CH395д����
* Input          : mCmd---��Ҫд��CH395��������
* Output         : None
* Return         : None
*******************************************************************************/
void xWriteCH395Cmd( UINT8 mCmd );



/*******************************************************************************
* Function Name  : xWriteCH395Data
* Description    : ��CH395д����
* Input          : mData---��Ҫд��CH395������
* Output         : None
* Return         : None
*******************************************************************************/
void xWriteCH395Data( UINT8 mData );

/*******************************************************************************
* Function Name  : xReadCH395Data
* Description    : ��CH395������
* Input          : None
* Output         : None
* Return         : ���ض�ȡ������
*******************************************************************************/
UINT8 xReadCH395Data( void );

/*******************************************************************************
* Function Name  : CH395_RST
* Description    : ��λ CH395
* Input          : None
* Output         : None
* Return         : �����ж�״̬
*******************************************************************************/
void CH395_RST( void );

UINT8 Query395Interrupt( void );

#endif