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
		
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��
	
//	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
    //B3  B4 ����Ϊ��������IO��
 
	//��IO������Ϊ��������
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|
	                              GPIO_Pin_10|GPIO_Pin_11;    
    GPIO_Init(GPIOA,&GPIO_InitStructure);
		
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8
	                        |GPIO_Pin_9|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;    
    GPIO_Init(GPIOB,&GPIO_InitStructure);
		
		//PC13 LED
		
	
	//IO��ӳ�䵽�ж���  12���ж�
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2 );//��GPIO���ӵ��ж���
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3 );//��GPIO���ӵ��ж���
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);//��GPIO���ӵ��ж���
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource5);//��GPIO���ӵ��ж���
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6 );//��GPIO���ӵ��ж���
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7 );//��GPIO���ӵ��ж���
   
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource10);//��GPIO���ӵ��ж���
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource11);//��GPIO���ӵ��ж���
    
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);//��GPIO���ӵ��ж���
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);//��GPIO���ӵ��ж���
	
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource8);//��GPIO���ӵ��ж���
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource9);//��GPIO���ӵ��ж���
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource12 );//��GPIO���ӵ��ж���
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource13 );//��GPIO���ӵ��ж���
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);//��GPIO���ӵ��ж���
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource15);//��GPIO���ӵ��ж���



  //GPIOB.0 �ж����Լ��жϳ�ʼ������   �½��ش��� F
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOB.1	  �ж����Լ��жϳ�ʼ������ �½��ش���  LF1
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOA.2	  �ж����Լ��жϳ�ʼ������  �½��ش���	LF2
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOA.3	  �ж����Լ��жϳ�ʼ������  �½��ش���	LF3
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOA.4	  �ж����Լ��жϳ�ʼ������  �½��ش���	L
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOA.5	  �ж����Լ��жϳ�ʼ������  �½��ش���	LB1
  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOA.6	  �ж����Լ��жϳ�ʼ������  �½��ش���	LB2
  	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOA.7	  �ж����Լ��жϳ�ʼ������  �½��ش���	B
  	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOB.8	  �ж����Լ��жϳ�ʼ������  �½��ش���	RB2
  	EXTI_InitStructure.EXTI_Line=EXTI_Line8;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOB.9    �ж����Լ��жϳ�ʼ������  �½��ش���	RB1
  	EXTI_InitStructure.EXTI_Line=EXTI_Line9;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOA.10	  �ж����Լ��жϳ�ʼ������  �½��ش���	R
  	EXTI_InitStructure.EXTI_Line=EXTI_Line10;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOA.11	  �ж����Լ��жϳ�ʼ������  �½��ش���	RF3
  	EXTI_InitStructure.EXTI_Line=EXTI_Line11;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOB.12	  �ж����Լ��жϳ�ʼ������  �½��ش���	RF2
  	EXTI_InitStructure.EXTI_Line=EXTI_Line12;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOB.13	  �ж����Լ��жϳ�ʼ������  �½��ش���	RF1
  	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOB.14	  �ж����Լ��жϳ�ʼ������  �½��ش���	
  	EXTI_InitStructure.EXTI_Line=EXTI_Line14;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOB.15	  �ж����Լ��жϳ�ʼ������  �½��ش���	
  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���




  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//�ⲿ�ж���0
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//�ⲿ�ж���1
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//�ⲿ�ж���2
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//�ⲿ�ж���3
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//�ⲿ�ж���4
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//�ⲿ�ж�5-9
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//�ⲿ�ж���10-15
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

 
}
