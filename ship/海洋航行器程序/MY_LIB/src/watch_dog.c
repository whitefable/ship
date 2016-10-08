#include "watch_dog.h"
#include "sys.h"


/********************************************
Brief:初始化独立看门狗
      时间计算：Tout = ((4*2^prer)*rlr)/40  ms
Parameter：     prer ---分频数  0~7 低3位有效
                分频因子 = 4*2^prer.最大只能是256！！！
								rlr  ---重装寄存器值  低11位有效
                
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
