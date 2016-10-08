#ifndef __TIMER_H
#define __TIMER_H
#include "stm32f10x.h"
#include "led.h"
#include "PWM_Out.h"

#define THRESHOLD_Little  3
#define THRESHOLD_Middle  5
#define THRESHOLD_Large  10
#define _TIM3_   											//ͨ���궨��ʹ��TIM4

typedef struct _Trigger
{
	//ǰ������
	uint8_t Trigger_F ; //Forward
	uint8_t Trigger_B ; //Back
	uint8_t Trigger_L ; //Left
	uint8_t Trigger_R ; //Right

	//��ǰ 1 2 3 4
	uint8_t Trigger_RF1 ;
	uint8_t Trigger_RF2 ;
	uint8_t Trigger_RF3 ;
	uint8_t Trigger_RF4 ; 
	 
	//��ǰ 1 2 3 4
	uint8_t Trigger_LF1 ;
	uint8_t Trigger_LF2 ;
	uint8_t Trigger_LF3 ;
	uint8_t Trigger_LF4 ;  

	//�Һ� 1 2
	uint8_t Trigger_RB1 ;
	uint8_t Trigger_RB2 ;
		 
	//��� 1 2
	uint8_t Trigger_LB1 ;
	uint8_t Trigger_LB2 ;   

}TRIGGER;


void TIM3_Init(u16 arr, u16 psc );


#endif



