/**
  ******************************************************************************
  * @author  yang feng wu
  * @version V1.0.0
  * @date    2019/10/12
  * @brief   ����8266
  ******************************************************************************
	һ,ʹ��˵��:
		1,��ʼ��ι��,ʱ��40K,��Ƶ��Ϊ256,156.25HZ,6.4ms;ι����С���5S
			IWDG_Init(IWDG_Prescaler_256,156*5);
			
		2,����ʹ��,ι��
			IWDG_Feed();
  ******************************************************************************
  */

#define IWDG_C_
#include "iwdg.h"

//��ʼ���������Ź�
//prer:��Ƶ��:0~7(ֻ�е�3λ��Ч!)
//��Ƶ����=4*2^prer.�����ֵֻ����256!
//rlr:��װ�ؼĴ���ֵ:��11λ��Ч.���4096
//ʱ�����(���):Tout=((4*2^prer)*rlr)/40 (ms).

void IWDG_Init( u8 prer, u16 rlr )
{
    IWDG_WriteAccessCmd( IWDG_WriteAccess_Enable ); //ʹ�ܶԼĴ���IWDG_PR��IWDG_RLR��д����

    IWDG_SetPrescaler( prer );                      //����IWDGԤ��Ƶֵ:����IWDGԤ��ƵֵΪ64

    IWDG_SetReload( rlr );                          //����IWDG��װ��ֵ

    IWDG_ReloadCounter();                           //����IWDG��װ�ؼĴ�����ֵ��װ��IWDG������

    IWDG_Enable();                                  //ʹ��IWDG
}

//ι�������Ź�
void IWDG_Feed( void  )
{
	IWDG_ReloadCounter();//reload
}

