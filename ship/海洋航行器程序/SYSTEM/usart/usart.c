
#include "usart.h"


#if 0

void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
	u8 Res;

	

	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断()
		{

		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		Res =USART_ReceiveData(USART1);    //(USART1->DR);	//读取接收到的数据
	
	//	LCD5110WriteChar(20,5,'r');

	
	
	    Temp[counter] = Res;   
	            //(USART1->DR);	//读取接收到的数据
	    if(counter==0&&Temp[0]!=0x55)   return ;
            	//如果0号数据不是数据头，跳过
	    counter++;
    	if(counter==11)
		{
		memcpy(ReceivedFromMPU,Temp,11);
    	counter = 0; //计数器清零，准备下一次接收
    	sign = 1;	 //接受完了一帧数据
		}

	
	   
	     
		}


			    
	} 
#endif


#if 0

void USART3_IRQHandler(void)                	//串口1中断服务程序
	{
	u8 Res;

	

	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断()
		{

		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
		Res =USART_ReceiveData(USART3);    //(USART1->DR);	//读取接收到的数据
	

		USART3_Send_One_Byte(Res);
	
	   
	     
		}


			    
	} 
#endif





void uart_init(u32 bound){

/*********************串口一初始化*********/
	
/*******************************************/

    //GPIO端口设置
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

   //Usart1 NVIC 配置

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器USART1
  
   //USART 初始化设置
   
	USART_InitStructure.USART_BaudRate = 115200;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);
   

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
   
    USART_Cmd(USART1, ENABLE);                    //使能串口

#endif 
/*********************串口3*************************
不用的话将1改为0
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

   //Usart1 NVIC 配置

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;		//

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器USART1
  
   //USART 初始化设置
   
	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART3, &USART_InitStructure);
   

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断
   
    USART_Cmd(USART3, ENABLE);                    //使能串口


#endif 

}



	void USART1_Send_One_Byte(u8 data)
	{
	   USART_SendData(USART1,data); //发送一位数据 
	   while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);//等待发送完毕 
	}



void USART3_Send_One_Byte(u8 data)
	{
		 
	   USART_SendData(USART3,data); //发送一位数据 
	   while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);//等待发送完毕 
	}
	
	
	
	//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要++
              
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;  
     
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*使用microLib的方法*/
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


