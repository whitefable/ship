#include "main.h"
//uint8_t kk;
u8 stflag;//start flag for motor
int main(void)
{
	  NVIC_Configuration();
	  delay_init(72);
	  EXTIS_Init();//�ж�
	
	  TIM3_Init(200,7200);//��ʱ20ms�ж�һ��
    
		LED_Init();
 		
	  TIM4_PWM_Init();//dianji  Pb7
		stflag=0;
    TIM2_PWM_Init();//duoji  PA 0
	  WatchDog_Init();//���TIM3һ����
		//TIM_SetCompare2(TIM4,800);
		//TIM_SetCompare1(TIM2,1650);
		//GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		//kk=0;
    while(1)
    {
//			delay_ms(300);//for sensor test
//			GPIO_SetBits(GPIOC, GPIO_Pin_13);				


		}		
  
}



