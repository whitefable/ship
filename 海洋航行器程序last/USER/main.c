#include "main.h"
uint8_t kk;
u8 stflag;//start flag for motor
u16 soft,test;
int main(void)
{
	  NVIC_Configuration();
	  delay_init(72);
	  EXTIS_Init();//中断
	
	  TIM3_Init(200,7200);//定时20ms中断一次
    
		LED_Init();
 		
	  TIM4_PWM_Init();//dianji  Pb7
		stflag=0;
    TIM2_PWM_Init();//duoji  PA 0
	  WatchDog_Init();//配合TIM3一起用
		//TIM_SetCompare2(TIM4,950);
		//TIM_SetCompare1(TIM2,2000);
		//GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		//test=600;
//		for(soft=100;soft<600;soft=soft+10)
//					{
//						delay_ms(100);
//						TIM_SetCompare2(TIM4,soft);
//					}
    while(1)
    {
				//TIM_SetCompare2(TIM4,test);
//			delay_ms(300);//for sensor test
//			GPIO_SetBits(GPIOC, GPIO_Pin_13);				


		}		
  
}



