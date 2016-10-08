#ifndef  __PWM_OUT_H
#define  __PWM_OUT_H
#include "sys.h"

#define PERIOD1 1000 
#define FREQ1   6        //频率8k  电机用
#define PERIOD2 20000
#define FREQ2   72      //周期 20ms  舵机用  

#define _TIM4_PWM_
#define _TIM2_PWM_

void TIM4_Init_PWM(u16 arr,u16 psc);
void TIM2_Init_PWM(u16 arr,u16 psc);

void TIM4_PWM_Init(void);
void TIM2_PWM_Init(void);



#endif
