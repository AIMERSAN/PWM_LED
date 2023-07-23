#ifndef __BOARD_LED_H
#define __BOARD_LED_H

#include "stm32f4xx.h"
#include "Drv_MCU.h"

#define LED0_GPIO_PORT GPIOE
#define LED1_GPIO_PORT GPIOE
#define LED2_GPIO_PORT GPIOG


#define led0On PEout(3);


#endif