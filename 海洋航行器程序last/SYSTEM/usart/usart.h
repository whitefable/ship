#ifndef __USART_H
#define __USART_H
#include "stdio.h"
#include "stm32f10x.h"
#include "led.h"


//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
////////////////////////////////////////////////////////////////////////////////// 


void USART1_Send_One_Byte(u8 data);



void USART3_Send_One_Byte(u8 data);





void uart_init(u32 bound);

#endif
