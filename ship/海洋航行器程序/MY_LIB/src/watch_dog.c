#include "watch_dog.h"
#include "sys.h"


/********************************************
Brief:��ʼ���������Ź�
      ʱ����㣺Tout = ((4*2^prer)*rlr)/40  ms
Parameter��     prer ---��Ƶ��  0~7 ��3λ��Ч
                ��Ƶ���� = 4*2^prer.���ֻ����256������
								rlr  ---��װ�Ĵ���ֵ  ��11λ��Ч
                
***********************************************/
void IWDG_Init(u8 prer,u16 rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  
	IWDG_SetPrescaler(prer);
	IWDG_SetReload(rlr);
	IWDG_ReloadCounter();
	IWDG_Enable();
}

	


void WatchDog_Init(void)
{
	IWDG_Init(PRER1,RLR1);
}

void Feed_WatchDog(void)
{
	IWDG_ReloadCounter();
}
