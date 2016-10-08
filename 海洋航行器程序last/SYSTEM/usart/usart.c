
#include "usart.h"


#if 0

void USART1_IRQHandler(void)                	//����1�жϷ������
	{
	u8 Res;

	

	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�()
		{

		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		Res =USART_ReceiveData(USART1);    //(USART1->DR);	//��ȡ���յ�������
	
	//	LCD5110WriteChar(20,5,'r');

	
	
	    Temp[counter] = Res;   
	            //(USART1->DR);	//��ȡ���յ�������
	    if(counter==0&&Temp[0]!=0x55)   return ;
            	//���0�����ݲ�������ͷ������
	    counter++;
    	if(counter==11)
		{
		memcpy(ReceivedFromMPU,Temp,11);
    	counter = 0; //���������㣬׼����һ�ν���
    	sign = 1;	 //��������һ֡����
		}

	
	   
	     
		}


			    
	} 
#endif


#if 0

void USART3_IRQHandler(void)                	//����1�жϷ������
	{
	u8 Res;

	

	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�()
		{

		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
		Res =USART_ReceiveData(USART3);    //(USART1->DR);	//��ȡ���յ�������
	

		USART3_Send_One_Byte(Res);
	
	   
	     
		}


			    
	} 
#endif





void uart_init(u32 bound){

/*********************����һ��ʼ��*********/
	
/*******************************************/

    //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

#if 0	 
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
     //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);  

   //Usart1 NVIC ����

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART1
  
   //USART ��ʼ������
   
	USART_InitStructure.USART_BaudRate = 115200;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);
   

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
   
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���

#endif 
/*********************����3*************************
���õĻ���1��Ϊ0
*****************************************************/	
#if 1

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
     //USART1_TX   PB.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
   
    //USART1_RX	  PB.11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);  

   //Usart1 NVIC ����

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;		//

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART1
  
   //USART ��ʼ������
   
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART3, &USART_InitStructure);
   

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�
   
    USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���


#endif 

}



	void USART1_Send_One_Byte(u8 data)
	{
	   USART_SendData(USART1,data); //����һλ���� 
	   while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);//�ȴ�������� 
	}



void USART3_Send_One_Byte(u8 data)
	{
		 
	   USART_SendData(USART3,data); //����һλ���� 
	   while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);//�ȴ�������� 
	}
	
	
	
	//�������´���,֧��printf����,������Ҫѡ��use MicroLIB
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ++
              
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;  
     
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/


