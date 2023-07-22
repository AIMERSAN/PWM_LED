/**
  ******************************************************************************
  * @file    Drv_Timer.h
  * @author  yuan hang
  * @version V1.0.0
  * @date    2023/06/11
  * @brief   定时器驱动h文件
  ******************************************************************************/
/


#ifndef __TIMER_H
#define __TIMER_H


#include "stm32f4xx.h"




void Timer2_Config(void);
void Timer3_PWM_Config(uint16_t perValue, uint16_t pscValue);

#endif

