#ifndef __USART1_H
#define __USART1_H

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stm32f4xx.h"

//����ʹ�õĴ���
#define UART_USE UART5

//����USARTʱ��
#define USART_CLK RCC_APB1Periph_UART5

//���崮�ڶ�Ӧ�ж��Լ��жϺ���
#define UART_Irqn UART5_IRQn
#define UART_IRQHandler UART5_IRQHandler

//����USART GPIO���ͽ��ն˿�
#define USART_TX_CLK  RCC_AHB1Periph_GPIOC
#define USART_TX_PORT GPIOC
#define USART_TX_PIN  GPIO_Pin_12

#define USART_RX_CLK  RCC_AHB1Periph_GPIOD
#define USART_RX_PORT GPIOD
#define USART_RX_PIN  GPIO_Pin_2

/* �������Ÿ��� */
#define USART_TX_AF GPIO_AF_UART5
#define USART_RX_AF GPIO_AF_UART5

#define USART_TX_Source GPIO_PinSource12
#define USART_RX_Source GPIO_PinSource2

//�����������ֽ��� 200
#define UART_REC_NUM  200

extern uint16_t USART_RX_STA;
extern u8 receive_str[UART_REC_NUM];

void uart_init(u32 bound);
void uartSendChars(u8 *str, u16 strlen);

#endif
