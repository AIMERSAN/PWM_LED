#ifndef __USART1_H
#define __USART1_H

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stm32f4xx.h"

//定义使用的串口
#define UART_USE UART5

//定义USART时钟
#define USART_CLK RCC_APB1Periph_UART5

//定义串口对应中断以及中断函数
#define UART_Irqn UART5_IRQn
#define UART_IRQHandler UART5_IRQHandler

//定义USART GPIO发送接收端口
#define USART_TX_CLK  RCC_AHB1Periph_GPIOC
#define USART_TX_PORT GPIOC
#define USART_TX_PIN  GPIO_Pin_12

#define USART_RX_CLK  RCC_AHB1Periph_GPIOD
#define USART_RX_PORT GPIOD
#define USART_RX_PIN  GPIO_Pin_2

/* 定义引脚复用 */
#define USART_TX_AF GPIO_AF_UART5
#define USART_RX_AF GPIO_AF_UART5

#define USART_TX_Source GPIO_PinSource12
#define USART_RX_Source GPIO_PinSource2

//定义最大接收字节数 200
#define UART_REC_NUM  200

extern uint16_t USART_RX_STA;
extern u8 receive_str[UART_REC_NUM];

void uart_init(u32 bound);
void uartSendChars(u8 *str, u16 strlen);

#endif
