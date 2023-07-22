
/**
  ******************************************************************************
  * @file    Drv_Timer.c
  * @author  YH
  * @version V1
  * @date    2019/10/13
  * @brief   字符串处理函数
  ******************************************************************************/



#include "Drv_Timer.h"

uint32_t Timer2Cnt=0;


/**
  * @brief  Tim2 Config
  * @param  None
  * @retval None
  * @brief  定时器2实现输出PWM波形，达到LED呼吸灯效果
  */

void Timer2_Config(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    //定时器2
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);

    /* Resets the TIM2 */
    TIM_DeInit(TIM2);
    //设置了时钟分割。
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    // 选择了计数器模式。
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    //初值
    TIM_TimeBaseStructure.TIM_Period = 10;//定时时间1ms进一次
    //设置了用来作为 TIMx 时钟频率除数的预分频值。72M / 7199+1 = 0.01M
    TIM_TimeBaseStructure.TIM_Prescaler = 7199;

    //TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);


    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    /* Enables the TIM2 counter */
    TIM_Cmd(TIM2, ENABLE);

    /* Enables the TIM2 Capture Compare channel 1 Interrupt source */
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE );
}

/**
  * @brief  Tim2 IRQ处理
  * @param  None
  * @retval None
  * @brief  定时器中断处理
  */
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        Timer2Cnt++;
    }
}





