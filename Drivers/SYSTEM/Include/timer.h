#ifndef __TIMER_H
#define __TIMER_H

#ifndef _TIME_C_//���û�ж���  _TIME_C_
#define _TIME_Ex_ extern
#else
#define _TIME_Ex_
#endif

#include "stm32f4xx.h"

_TIME_Ex_ u32 Timer2Cnt;

_TIME_Ex_ void Timer2_Config(void);


#endif
