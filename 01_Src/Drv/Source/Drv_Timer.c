
/**
  ******************************************************************************
  * @file    Drv_Timer.c
  * @author  YH
  * @version V1
  * @date    2019/10/13
  * @brief   �ַ���������
  ******************************************************************************/



#include "Drv_Timer.h"

uint32_t Timer2Cnt=0;

/**
  * @brief  Tim2 Config
  * @param  None
  * @retval None
  * @brief  ��ʱ��2���ã�ʵ��LED��������˸
  */
void Timer2_Config(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    //��ʱ��2
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);

    /* Resets the TIM2 */
    TIM_DeInit(TIM2);
    //������ʱ�ӷָ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    // ѡ���˼�����ģʽ��
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    //��ֵ
    TIM_TimeBaseStructure.TIM_Period = 10;//��ʱʱ��1ms��һ��
    //������������Ϊ TIMx ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ��72M / 7199+1 = 0.01M
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
  * @brief  Tim3 PWM����
  * @param  uint16_t perValue Ԥװ��ֵ
  * @param  uint16_t pscValue Ԥ��Ƶֵ
  * @retval None
  * @brief  ��ʱ��3ʵ�����PWM���Σ����߼������ǹ۲�
  */
void Timer3_PWM_Config(uint16_t perValue, uint16_t pscValue)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseINitStructure;
    TIM_OCInitTypeDef       TIM_OCInitStructure;
    GPIO_InitTypeDef        GPIO_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    // PC6��ΪTIM3 CH1��PWM�������ӦGPIO����
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    TIM_DeInit(TIM3);
    
    // TIM3 ʱ����ʼ������
    TIM_TimeBaseINitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseINitStructure.TIM_Period      = perValue;
    TIM_TimeBaseINitStructure.TIM_Prescale    = pscValue;
    TIM_TimeBaseINitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM3, TIM_TimeBaseINitStructure);  

    //TIM3 CH1 PWMģʽ��ʼ������
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_Low;
    TIM_OC1Init(TIM3, TIM_OCInitStructure);

    TIM_ARRPreloadConfig(TIM3, ENABLE);

    // ʹ��TIM3��CCR1�����Ԥװ����
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

}


/**
  * @brief  Tim2 IRQ����
  * @param  None
  * @retval None
  * @brief  ��ʱ���жϴ���
  */
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        Timer2Cnt++;
    }
}





