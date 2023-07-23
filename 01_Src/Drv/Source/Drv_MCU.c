/**
  ******************************************************************************
  * @file    Drv_MCU.c 
  * @author  YH
  * @version V1.0
  * @date    20-June-2023
  * @brief   
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

#include "stm32f4xx.h"
#include "Drv_MCU.h"

/**
  * @brief  使用任意16位IO口组成16位输出的并口
  * @param  gpioGroup *group 任意16个IO口为元素的结构体指针
  * @param  uint16_t outData 16位输出数值
  * @retval None
  * @note   outData从高位开始赋值
  */
void gpioGroupOut(gpioGroup *group, uint16_t outData)
{
    for(uint8_t t = 0; t < 16; t++)
    {
        if((outData & 0x8000) >> 15)
        {
            switch (t)
            {
            case 0: group->data15 = 1; break;
            case 1: group->data14 = 1; break;
            case 2: group->data13 = 1; break;
            case 3: group->data12 = 1; break;
            case 4: group->data11 = 1; break;
            case 5: group->data10 = 1; break;
            case 6: group->data9  = 1; break;
            case 7: group->data8  = 1; break;
            case 8: group->data7  = 1; break;
            case 9: group->data6  = 1; break;
            case 10: group->data5  = 1; break;    
            case 11: group->data4  = 1; break;    
            case 12: group->data3  = 1; break;
            case 13: group->data2  = 1; break;
            case 14: group->data1  = 1; break;
            case 15: group->data0  = 1; break;
            }
        }
        else
        {
            switch (t)
            {
            case 0: group->data15 = 0; break;
            case 1: group->data14 = 0; break;
            case 2: group->data13 = 0; break;
            case 3: group->data12 = 0; break;
            case 4: group->data11 = 0; break;
            case 5: group->data10 = 0; break;
            case 6: group->data9  = 0; break;
            case 7: group->data8  = 0; break;
            case 8: group->data7  = 0; break;
            case 9: group->data6  = 0; break;
            case 10: group->data5  = 0; break;    
            case 11: group->data4  = 0; break;    
            case 12: group->data3  = 0; break;
            case 13: group->data2  = 0; break;
            case 14: group->data1  = 0; break;
            case 15: group->data0  = 0; break;
            }
        }
        outData <<= 1;
    }
}

/**
  * @brief  位带操作实现，同一IO的几位并行输出操作
  * @param  GPIO_TypeDef* GPIOx: 需要操作的IO口
  * @param  uint8_t startBit: 并行输出的起始位 
  * @param  uint8_t bitSize:  并行输出的位数
  * @param  uint16_t outData: 并行输出的数据
  * @retval None
  * @note   outData从高位开始赋值
  */
void gpioBitsOut(GPIO_TypeDef* GPIOx, uint8_t startBit, uint8_t bitSize, uint16_t outData)
{
    uint8_t i = 0;
    uint16_t bul = 0;
    uint16_t middledata = 1;

    if(bitSize > (16 - startBit))
    {
        bitSize = 16 - startBit;
    }
    
    i = startBit;
    if(i > 0)
    {
        while(i--)
        {
            bu1 += middata;
            middata *= 2;
        }
    }

    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    GPIOx->ODR &= (((0xffff << bit_size) << start_bit) | bu1);
    GPIOx->ODR |= (outdata << start_bit);
}

void delayInit()
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    fac_us = SYSCLK / 8;
    fac_ms = (uint16_t)fac_us * 1000; //每个ms需要的systick时钟数
}

void delayUs(uint32_t nus)
{
    uint32_t midtime;
    SysTick->LOAD = nus * fac_us; //时间加载
    SysTick->VAL = 0x00;        //清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;          //开始倒数
    do
    {
        midtime = SysTick->CTRL;
    }
    while((midtime & 0x01) && !(midtime & (1 << 16)));//等待时间到达
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
    SysTick->VAL = 0X00;       //清空计数器
}

static void delay_xms(uint16_t nms)
{
    uint32_t midtime;
    SysTick->LOAD = (uint32_t)nms * fac_ms;//时间加载(SysTick->LOAD为24bit)
    SysTick->VAL = 0x00;           //清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;          //开始倒数
    do
    {
        midtime = SysTick->CTRL;
    }
    while((midtime & 0x01) &&! (midtime & (1 << 16)));//等待时间到达
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
    SysTick->VAL = 0X00;       //清空计数器
}

void delay_ms(uint16_t nms)
{
    /*  这里用540,是考虑到某些客户可能超频使用,
        比如超频到248M的时候,delay_xms最大只能延时541ms左右了 */
    u8 repeat = nms / 540;	
    uint16_t remain = nms % 540;
    while(repeat)
    {
        delay_xms(540);
        repeat--;
    }
    if(remain)
        delay_xms(remain);
}