#include "exti.h"

u16 Count[16] = {0};

void EXTI0_IRQHandler(void)                  //F
{
	if( EXTI_GetITStatus(EXTI_Line0) != RESET )
	{
		EXTI_ClearITPendingBit(EXTI_Line0);
		Count[0]++;      
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	}
	
}

void EXTI1_IRQHandler(void)//LF1
{
	if( EXTI_GetITStatus(EXTI_Line1) != RESET )
	{
		EXTI_ClearITPendingBit(EXTI_Line1);
		Count[1]++;
	}
	
}

void EXTI2_IRQHandler(void)//LF2
{
	if( EXTI_GetITStatus(EXTI_Line2) != RESET )
	{
		EXTI_ClearITPendingBit(EXTI_Line2);
		Count[2]++;
		
	}
	
}

void EXTI3_IRQHandler(void)//LF3
{
	if( EXTI_GetITStatus(EXTI_Line3) != RESET )
	{
		EXTI_ClearITPendingBit(EXTI_Line3);
		Count[3]++;
	}
	
}

void EXTI4_IRQHandler(void)//L
{
	if( EXTI_GetITStatus(EXTI_Line4) != RESET )
	{
		EXTI_ClearITPendingBit(EXTI_Line4);
		Count[4]++;
	}
	
}

void EXTI9_5_IRQHandler(void)//LB
{
	if( EXTI_GetITStatus(EXTI_Line5) != RESET )
	{
		EXTI_ClearITPendingBit(EXTI_Line5);
		Count[5]++;
	}
	
	if( EXTI_GetITStatus(EXTI_Line6) != RESET )//B
	{
		EXTI_ClearITPendingBit(EXTI_Line6);
		Count[6]++;
	}
	
	if( EXTI_GetITStatus(EXTI_Line7) != RESET )//RB
	{
		EXTI_ClearITPendingBit(EXTI_Line7);
		Count[7]++;
	}
	
	if( EXTI_GetITStatus(EXTI_Line8) != RESET )//R
	{
		EXTI_ClearITPendingBit(EXTI_Line8);
		Count[8]++;
	}
	
    if( EXTI_GetITStatus(EXTI_Line9) != RESET )//RF3
	{
		EXTI_ClearITPendingBit(EXTI_Line9);
		Count[9]++;
 	}
}

void EXTI15_10_IRQHandler(void)//RF2
{
	if( EXTI_GetITStatus(EXTI_Line10) != RESET )
	{
		EXTI_ClearITPendingBit(EXTI_Line10);
		Count[10]++;
	}
	
	if( EXTI_GetITStatus(EXTI_Line11) != RESET )//RF1
	{
		EXTI_ClearITPendingBit(EXTI_Line11);
		Count[11]++;
	}
	
	if( EXTI_GetITStatus(EXTI_Line12) != RESET )
	{
		EXTI_ClearITPendingBit(EXTI_Line12);
		Count[12]++;
	}
	
	if( EXTI_GetITStatus(EXTI_Line13) != RESET )
	{
		EXTI_ClearITPendingBit(EXTI_Line13);
		Count[13]++;	
	}
	
    if( EXTI_GetITStatus(EXTI_Line14) != RESET )
	{
		EXTI_ClearITPendingBit(EXTI_Line14);
		Count[14]++;
	

	}
	
	 if( EXTI_GetITStatus(EXTI_Line15) != RESET )
	{
		EXTI_ClearITPendingBit(EXTI_Line15);
		Count[15]++;
	}

}






void EXTIS_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
	
//	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
    //B3  B4 设置为正常数字IO口
 
	//将IO口设置为上拉输入
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|
	                              GPIO_Pin_10|GPIO_Pin_11;    
    GPIO_Init(GPIOA,&GPIO_InitStructure);
		
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8
	                        |GPIO_Pin_9|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;    
    GPIO_Init(GPIOB,&GPIO_InitStructure);
		
		//PC13 LED
		
	
	//IO口映射到中断线  12个中断
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2 );//把GPIO连接到中断上
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3 );//把GPIO连接到中断上
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);//把GPIO连接到中断上
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource5);//把GPIO连接到中断上
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6 );//把GPIO连接到中断上
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7 );//把GPIO连接到中断上
   
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource10);//把GPIO连接到中断上
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource11);//把GPIO连接到中断上
    
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);//把GPIO连接到中断上
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);//把GPIO连接到中断上
	
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource8);//把GPIO连接到中断上
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource9);//把GPIO连接到中断上
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource12 );//把GPIO连接到中断上
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource13 );//把GPIO连接到中断上
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);//把GPIO连接到中断上
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource15);//把GPIO连接到中断上



  //GPIOB.0 中断线以及中断初始化配置   下降沿触发 F
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 //GPIOB.1	  中断线以及中断初始化配置 下降沿触发  LF1
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 //GPIOA.2	  中断线以及中断初始化配置  下降沿触发	LF2
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 //GPIOA.3	  中断线以及中断初始化配置  下降沿触发	LF3
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 //GPIOA.4	  中断线以及中断初始化配置  下降沿触发	L
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 //GPIOA.5	  中断线以及中断初始化配置  下降沿触发	LB1
  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 //GPIOA.6	  中断线以及中断初始化配置  下降沿触发	LB2
  	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 //GPIOA.7	  中断线以及中断初始化配置  下降沿触发	B
  	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 //GPIOB.8	  中断线以及中断初始化配置  下降沿触发	RB2
  	EXTI_InitStructure.EXTI_Line=EXTI_Line8;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 //GPIOB.9    中断线以及中断初始化配置  下降沿触发	RB1
  	EXTI_InitStructure.EXTI_Line=EXTI_Line9;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 //GPIOA.10	  中断线以及中断初始化配置  下降沿触发	R
  	EXTI_InitStructure.EXTI_Line=EXTI_Line10;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 //GPIOA.11	  中断线以及中断初始化配置  下降沿触发	RF3
  	EXTI_InitStructure.EXTI_Line=EXTI_Line11;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 //GPIOB.12	  中断线以及中断初始化配置  下降沿触发	RF2
  	EXTI_InitStructure.EXTI_Line=EXTI_Line12;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 //GPIOB.13	  中断线以及中断初始化配置  下降沿触发	RF1
  	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 //GPIOB.14	  中断线以及中断初始化配置  下降沿触发	
  	EXTI_InitStructure.EXTI_Line=EXTI_Line14;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 //GPIOB.15	  中断线以及中断初始化配置  下降沿触发	
  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器




  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//外部中断线0
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//外部中断线1
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//外部中断线2
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//外部中断线3
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//外部中断线4
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//外部中断5-9
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//外部中断线10-15
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

 
}
