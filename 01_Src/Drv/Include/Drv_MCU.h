#ifndef __DRV_MCU_H
#define __DRV_MCU_H

typedef struct 
{
    uint16_t data0:1;
    uint16_t data1:1;
    uint16_t data2:1;
    uint16_t data3:1;
    uint16_t data4:1;
    uint16_t data5:1;
    uint16_t data6:1;
    uint16_t data7:1;
    uint16_t data8:1;
    uint16_t data9:1;
    uint16_t data10:1;
    uint16_t data11:1;
    uint16_t data12:1;
    uint16_t data13:1;
    uint16_t data14:1;
    uint16_t data15:1;
}gpioGroup;

/* 
    位带操作定义，映射公式: 
    bit_word_addr = bit_band_base + (byte_offset * 32) + (bit_number * 4)
*/
#define BITBAND(addr, bitNum)   ((addr & 0xF0000000) + 0x20000000 +      \
                                ((addr & 0xFFFFF) << 5) + (bitNum << 2)) \  

#define MEM_ADDR(addr) *((volatile unsigned long *) (addr))

#define BIT_ADDR(addr, bitNum) MEM_ADDR(BITBAND(addr, bitNum))

// 定义IO口地址映射
#define GPIOA_ODR_Addr (GPIOA_BASE + 20)
#define GPIOB_ODR_Addr (GPIOB_BASE + 20)
#define GPIOC_ODR_Addr (GPIOC_BASE + 20)
#define GPIOD_ODR_Addr (GPIOD_BASE + 20)
#define GPIOE_ODR_Addr (GPIOE_BASE + 20)
#define GPIOF_ODR_Addr (GPIOF_BASE + 20)
#define GPIOG_ODR_Addr (GPIOG_BASE + 20)
#define GPIOH_ODR_Addr (GPIOH_BASE + 20)
#define GPIOI_ODR_Addr (GPIOI_BASE + 20)

#define GPIOA_IDR_Addr (GPIOA_BASE + 16)
#define GPIOB_IDR_Addr (GPIOB_BASE + 16)
#define GPIOC_IDR_Addr (GPIOC_BASE + 16)
#define GPIOD_IDR_Addr (GPIOD_BASE + 16)
#define GPIOE_IDR_Addr (GPIOE_BASE + 16)
#define GPIOF_IDR_Addr (GPIOF_BASE + 16)
#define GPIOG_IDR_Addr (GPIOG_BASE + 16)
#define GPIOH_IDR_Addr (GPIOH_BASE + 16)
#define GPIOI_IDR_Addr (GPIOI_BASE + 16)

// 单一IO口操作
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr, n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr, n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr, n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr, n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr, n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr, n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr, n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr, n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr, n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr, n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr, n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr, n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr, n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr, n)  //输入

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr, n)  //输出 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr, n)  //输入

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr, n)  //输出 
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr, n)  //输入

void gpioGroupOut(gpioGroup *group, uint16_t outData);
void gpioBitsOut(GPIO_TypeDef* GPIOx, uint8_t startBit, uint8_t bitSize, uint16_t outData);
void delayInit();
void delayUs(uint32_t nus);
static void delay_xms(uint16_t nms);
void delay_ms(uint16_t nms);
#endif