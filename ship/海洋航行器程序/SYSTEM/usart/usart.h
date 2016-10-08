#ifndef __USART_H
#define __USART_H
#include "stdio.h"
#include "stm32f10x.h"
#include "led.h"


//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
////////////////////////////////////////////////////////////////////////////////// 


void USART1_Send_One_Byte(u8 data);



void USART3_Send_One_Byte(u8 data);





void uart_init(u32 bound);

#endif
