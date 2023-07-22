/**
  ******************************************************************************
  * @file    main.c
  * @author
  * @version V1.8.1
  * @date    27-January-2022
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "Drv_Uart.h"
#include "Drv_Timer.h"
//#include "iwdg.h"



/** @addtogroup
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
//    NVIC_Configuration();
//    uart_init( 115200 );
//    delay_init(); 
//    
//    /* 初始化CH395，拉高CS引脚 */
//    CH395_PORT_INIT();
//    delay_ms(200);
//    CH395_RST();
//    delay_ms(200);
//    
//    printf( "\r\nCH395 start\r\n" );
    
    /* Infinite loop */
    while (1)
    { 
//		delay_ms( 1000 );
//        printf( "CH395Ver : %2x\n", CH395CMDGetVer() );
//        delay_ms( 1000 );
//        // printf( "CH395 Staut : %2x\n", CH395CMDCheckExist( 0x57 ) );
//		// printf( "test\n" );

    }
}
