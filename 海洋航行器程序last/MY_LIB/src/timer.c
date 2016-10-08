#include "timer.h"
#include "control.h"
#include "watch_dog.h"

/*************************************
				��ʱ��4���ڴ�����������
*************************************/
uint16_t  ucRecSign = 0;
uint16_t LastucRecSign=0;
uint16_t recsigntemp;

extern uint16_t Count[16];							//��������������

uint16_t  CountTmp[16]={0};							//�м����
uint16_t  counttest[16]={0};
uint8_t Pri[16];//priority of each sensor high for high <256
u8 fil;//signal filter flag
u8 lr;//orientation
u8 lf,rf,lb,rb;

/*********************����״̬����******************************/
TRIGGER Trigger_Variables;
/******************************************************************/


/**********************������Ʊ�������*********************************/
TRIGGER Steer_Valve;
/*******************************************************************/


uint8_t Error = 0;

uint8_t MaxVal = 0;

uint8_t LeftVal_F = 0;   //LF
uint8_t RightVal_F = 0;  //RF
uint8_t LeftVal_B = 0;   //LB
uint8_t RightVal_B = 0;  //RB



uint8_t LMR_State = 1;   //����״̬����  0-��ǰ��  1-��ǰ�� 2-��ǰ��
                         //								3-�Һ�    4-���     
uint8_t LMR_Last_State= 1;
#ifdef _TIM3_

void TIM3_Init(uint16_t arr, uint16_t psc )   //20ms
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_Period = arr;//arr-1 //�趨�������Զ���װֵ 
	TIM_TimeBaseInitStructure.TIM_Prescaler =psc-1; 	//Ԥ��Ƶ��   
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	TIM_ClearFlag(TIM3, TIM_FLAG_Update); 
	 
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM3, ENABLE); 
	//������ȼ�,
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ;     
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;    
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;           
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              
	NVIC_Init(&NVIC_InitStructure); 

}
	#endif


uint8_t Find_Max(uint8_t num1,uint8_t num2,uint8_t num3,uint8_t num4)
{
	uint8_t max;
	uint8_t temp;
	temp = num1>num2?num1:num2;
	temp = temp>num3?temp:num3;
	max  = temp>num4?temp:num4;
	return max;
}

#ifdef _TIM3_
/***************TIM4�ж�******************/
/*�����������ݣ�����ֵ�ж�*/
/********************************************/


void TIM3_IRQHandler(void)  
{
	static uint8_t flag_control=0,flag_caculate=0,k=0;
	
	
  if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		
	/////////////////////////////////////////////////////////////////////////////
		if(++flag_control==2)   //���ʱ��40ms  ����������
		{
			flag_control=0;
			
			Steer_Control();  //duoji
			Motor_Control();  //dianji
		}

		if(++flag_caculate==13)   //���ʱ��260ms  ͬʱι��
		{
			Feed_WatchDog();
			flag_caculate=0;
					
			for(k=0;k<16;k++)
			{
				CountTmp[k] = Count[k];//�м����
				Count[k] = 0; //��������
				counttest[k] = counttest[k] + CountTmp[k];
			}
			
			
			for(k=0;k<16;k++)//�ж��Ƿ񴥷�  set bit to k
			{

					if(CountTmp[k]>THRESHOLD_Little)//threshold
							 ucRecSign |= 1<<k;
					else
							ucRecSign &= ~(1<<k);
			}		
			
			//����״̬������ֵ
			if(ucRecSign&0x0001)  //0  F
			{   
				Trigger_Variables.Trigger_F=1;//����ǰ״̬ 
			  Steer_Valve.Trigger_F=0;//
				Pri[0]=100;
			}
			else                    
			{  
				Trigger_Variables.Trigger_F=0;//������F״̬ 
			  Steer_Valve.Trigger_F=0;//
				Pri[0]=0;
			}
			if(ucRecSign&0x0002)   	//1 LF1
			{	
			 
				Trigger_Variables.Trigger_LF1=1;//������1״̬ 
				Steer_Valve.Trigger_LF1=3;//��ƫ�̶�345867
				Pri[1]=6;
			}
			else                    
			{	
				Trigger_Variables.Trigger_LF1=0;//������LF1
				Steer_Valve.Trigger_LF1=0;//
				Pri[1]=0;
			}
			if(ucRecSign&0x0004)   	//2  LF2
			{	
				Trigger_Variables.Trigger_LF2=1;//������2״̬ 
				Steer_Valve.Trigger_LF2=6;//��ƫ�̶�359 14 12 10
				Pri[2]=10;
			}
			else                    
			{				 
				Trigger_Variables.Trigger_LF2=0;//������LF1 
				Steer_Valve.Trigger_LF2=0;
				Pri[2]=0;
			}
				
			if(ucRecSign&0x0008)   //3 LF3
			{					 
				Trigger_Variables.Trigger_LF3=1;//������3״̬ 
				Steer_Valve.Trigger_LF3=9;//��ƫ�̶�5
				Pri[3]=15;
			}
			else                    
			{	 
				Trigger_Variables.Trigger_LF3=0;// 
				Steer_Valve.Trigger_LF3=0;//
				Pri[3]=0;
			}
					
			if(ucRecSign&0x0010)   	//4 L
			{
			 Trigger_Variables.Trigger_L=1;//������״̬ 
			 Steer_Valve.Trigger_L=14;//��ƫ�̶�7
			 Pri[4]=16;
			}
			else                   
			{
			  Trigger_Variables.Trigger_L=0;//
			  Steer_Valve.Trigger_L=0;//		
				Pri[4]=0;
			}
			
			if(ucRecSign&0x0020)   	//5 LB1
			{
			 Trigger_Variables.Trigger_LB1=1;//����ǰ״̬ 
			 Steer_Valve.Trigger_LB1=12;//
			 Pri[5]=9;//13
			}
			else                   
			{
			  Trigger_Variables.Trigger_LB1=0;//����LB1״̬ 
			  Steer_Valve.Trigger_LB1=0;//ƫת�̶�1		
				Pri[5]=0;
			}
	
			if(ucRecSign&0x0040)   	//6 LB2
			{
				Trigger_Variables.Trigger_LB2=1;//����LB2
				Steer_Valve.Trigger_LB2=10;//ƫת�̶�
				Pri[6]=14;
			}
			else                    
			{
				Trigger_Variables.Trigger_LB2=0;//����
				Steer_Valve.Trigger_LB2=0;//
				Pri[6]=0;
			}
			
			
			if(ucRecSign&0x0080)   	//7 B
			{
				Trigger_Variables.Trigger_B=1;//����B
				Steer_Valve.Trigger_B=0;//
				Pri[7]=16;
			}
			else                    
			{
				Trigger_Variables.Trigger_B=0;//
				Steer_Valve.Trigger_B=0;//
				Pri[7]=0;
			}
			
			
			if(ucRecSign&0x0100)   	//8 RB2
			{  
				Trigger_Variables.Trigger_RB2=1;//������
				Steer_Valve.Trigger_RB2=10;//��ƫת�̶�7
				Pri[8]=14;
			}
			else                    
			{    
				Trigger_Variables.Trigger_RB2=0;//������3״̬ 
				Steer_Valve.Trigger_RB2=0;//��ƫת�̶�3
				Pri[8]=0;
			}
					
			if(ucRecSign&0x0200)   	//9 RB1
			{  
				Trigger_Variables.Trigger_RB1=1;//������
				Steer_Valve.Trigger_RB1=12;//��ƫת�̶�7
				Pri[9]=9;//13
			}
			else                    
			{    
				Trigger_Variables.Trigger_RB1=0;//������3״̬ 
				Steer_Valve.Trigger_RB1=0;//��ƫת�̶�3
				Pri[9]=0;
			}
			
			if(ucRecSign&0x0400)   	//10 R
			{  
				Trigger_Variables.Trigger_R=1;//������
				Steer_Valve.Trigger_R=14;//��ƫת�̶�7
				Pri[10]=16;
			}
			else                    
			{    
				Trigger_Variables.Trigger_R=0;//������3״̬ 
				Steer_Valve.Trigger_R=0;//��ƫת�̶�3
				Pri[10]=0;
			}
			
			if(ucRecSign&0x0800)   	//11 RF3
			{
				Trigger_Variables.Trigger_RF3=1;//������0״̬ 
				Steer_Valve.Trigger_RF3=9;//��0ƫת�̶�
				Pri[11]=15;
			}
			else                    
			{
				Trigger_Variables.Trigger_RF3=0;//������0״̬ 
				Steer_Valve.Trigger_RF3=0;//��0ƫת�̶�
				Pri[11]=0;
			}
			
			
			if(ucRecSign&0x1000)   	//12 RF2
			{
				Trigger_Variables.Trigger_RF2=1;//�����Һ�1״̬ 
				Steer_Valve.Trigger_RF2=5;//�Һ�ƫת�̶�6
				Pri[12]=10;
			}
			else                    
			{
				Trigger_Variables.Trigger_RF2=0;//�����Һ�1״̬ 
				Steer_Valve.Trigger_RF2=0;//�Һ�ƫת�̶�6
				Pri[12]=0;
			}
			
			
			if(ucRecSign&0x2000)   	//13 RF1
			{
				Trigger_Variables.Trigger_RF1=1;//�����Һ�2״̬ 
				Steer_Valve.Trigger_RF1=2;//�Һ�ƫת�̶�5
				Pri[13]=6;
			}
			else                    
			{
				Trigger_Variables.Trigger_RF1=0;//�����Һ�2״̬ 
				Steer_Valve.Trigger_RF1=0;//�Һ�ƫת�̶�0		
				Pri[13]=0;
			}
			
//			
			if(ucRecSign&0x4000)   	//14  LF4
			{
				Trigger_Variables.Trigger_LF4=1;//������״̬ 
				Steer_Valve.Trigger_LF4=8;//�Һ�ƫת�̶�0
				Pri[14]=1;
			}
			else                    
			{
				Trigger_Variables.Trigger_LF4=0;//������״̬ 
				Steer_Valve.Trigger_LF4=0;//�Һ�ƫת�̶�0
				Pri[14]=0;
			}
			
			
			if(ucRecSign&0x8000)   	//15   RF4
			{
				Trigger_Variables.Trigger_RF4=1;    //�������״̬ 
				Steer_Valve.Trigger_RF4=8;         //���ƫת�̶�1
				Pri[15]=1;
			}
			else                   
			{	
			  Trigger_Variables.Trigger_RF4=0;  //�������״̬ 
				Steer_Valve.Trigger_RF4=0;        //���ƫת�̶�1
				Pri[15]=0;
			}
			
			LeftVal_F  = Find_Max(Steer_Valve.Trigger_LF1, Steer_Valve.Trigger_LF2,
												Steer_Valve.Trigger_LF3, Steer_Valve.Trigger_LF4);			
			RightVal_F = Find_Max(Steer_Valve.Trigger_RF1, Steer_Valve.Trigger_RF2,
													Steer_Valve.Trigger_RF3, Steer_Valve.Trigger_RF4);	

			LeftVal_B  = Find_Max(Steer_Valve.Trigger_L, Steer_Valve.Trigger_LB1,
												Steer_Valve.Trigger_LB2,0);			
			RightVal_B  = Find_Max(Steer_Valve.Trigger_R, Steer_Valve.Trigger_RB1,
												Steer_Valve.Trigger_RB2,0);		
												
//			LeftVal_F  = Find_Max(Steer_Valve.Trigger_LF1, Steer_Valve.Trigger_LF2,
//												Steer_Valve.Trigger_LF3, Steer_Valve.Trigger_L);			
//			RightVal_F = Find_Max(Steer_Valve.Trigger_RF1, Steer_Valve.Trigger_RF2,
//													Steer_Valve.Trigger_RF3, Steer_Valve.Trigger_R);	

//			LeftVal_B  = Find_Max(Steer_Valve.Trigger_LB1,Steer_Valve.Trigger_LB2,0,0);			
//			RightVal_B  = Find_Max(Steer_Valve.Trigger_RB1,Steer_Valve.Trigger_RB2,0,0);														
/*****************************************************************************/	
			lf=Pri[1]+Pri[2]+Pri[3];
			rf=Pri[13]+Pri[12]+Pri[11];
			lb=Pri[5]+Pri[6];
			rb=Pri[8]+Pri[9];
			if((Trigger_Variables.Trigger_F) && ((Pri[0]+lf+rf) > (Pri[7]+Pri[6]+Pri[8])))
			{//Forward
				if((Pri[1]+Pri[2]+Pri[3]) == (Pri[13]+Pri[12]+Pri[11]))
				{
					lr=0;//F
				}
				else
				{
					if(Pri[3] || Pri[11])
						Error=4;
					else if (Pri[12] || Pri [2])
						Error=2;
					else
						Error=1;
					if(lf>rf)
						lr=1;//L
					else
						lr=2;//R
				}
			}
			else if((Trigger_Variables.Trigger_B) && ((Pri[0]+lf+rf) < (Pri[7]+Pri[6]+Pri[8])))
			{//Backward
				Error=10;
				if(lb>rb)
					lr=1;
				else
					lr=2;//��������ת����ͷ
			}
			else//L R //only L or only R
			{
				if((lf>rf)&&(lb<rb))//lf || rb
				{
					Error=10;
					if(Trigger_Variables.Trigger_L || Trigger_Variables.Trigger_R)
					{
						if(~Trigger_Variables.Trigger_R)
							lr=1;
						else if(~Trigger_Variables.Trigger_L)
							lr=2;
						else//both triggered
						{
							if(lf>rb)
								lr=1;
							else
								lr=2;
						}
					}
					else//no L R pri 123 & pri 89
					{
						if(lf>rb)
						{
							if(~Trigger_Variables.Trigger_LF3)
								Error=4;
							lr=1;
						}
						else
							lr=2;
					}
				}
				else if((lf<rf)&&(lb>rb))//lb || rf
				{
					Error=10;
					if(Trigger_Variables.Trigger_L || Trigger_Variables.Trigger_R)
					{
						if(~Trigger_Variables.Trigger_R)
							lr=1;
						else if(~Trigger_Variables.Trigger_L)
							lr=2;
						else//both triggered
						{
							if(rf>lb)
								lr=2;
							else
								lr=1;
						}
					}
					else//no L R pri 123 & pri 89
					{
						if(rf>lb)
						{
							if(~Trigger_Variables.Trigger_RF3)
								Error=4;
							lr=2;
						}
						else
							lr=1;
					}
				}
				else if((lf+lb+Pri[4])>(rf+rb+Pri[10]))//left *left/right sensor added
				{
					lr=1;
					//if(Pri[3]+Pri[4]+Pri[5]>110)
					if(Pri[1]==0)
						Error=10;
					else
						Error=4;
				}
				else if((lf+lb+Pri[4])<(rf+rb+Pri[10]))//right *add like previous
				{
					lr=2;
					//if(Pri[11]+Pri[10]+Pri[9]>110)
					if(Pri[13]==0)	
						Error=10;
					else
						Error=4;
				}
				else if (Trigger_Variables.Trigger_L || Trigger_Variables.Trigger_R)
				{
					Error=10;
					if(Trigger_Variables.Trigger_L)
						lr=1;
					else
						lr=2;
				}
				else
				{
					//nothing happened...keep the last state
				}
			}
/*****************************************************************************/	
			//ǰ��Ÿ�����
			//LMR_Last_State = LMR_State;
//			if(LeftVal_F!=0||RightVal_F!=0)  //LF   RF
//			{
//			
//				if(LeftVal_F>RightVal_F)
//				{
//					MaxVal = LeftVal_F;
//					LMR_State = 0;             //��ǰ�ߴ���
//					Error = MaxVal;		
//				}
//				else if(LeftVal_F<RightVal_F)
//				{
//					MaxVal = RightVal_F;
//					LMR_State = 2;             //��ǰ�ߴ���
//					Error = MaxVal;		
//				}
//				else 
//				{
//					Error = 0;
//					LMR_State = 1;             //����ֱ��
//				}
//			}
//			//���ǰ��Ÿ�û����
//			else  
//			{
//				if(LeftVal_B!=0||RightVal_B!=0)
//					{
//						  //ǰ��Ÿ�û������ǰ���º��治�Գƴ���
//							if(LeftVal_B>RightVal_B)//LB>RB
//							{
//								MaxVal = LeftVal_B;
//								LMR_State = 0; //���ߴ���
//								Error = MaxVal;		
//							}
//							else if(LeftVal_B<RightVal_B)
//							{
//								MaxVal = RightVal_B;
//								LMR_State = 2; //�Һ�ߴ���
//								Error = MaxVal;		
//							}
////							//ǰ��Ÿ�û������ǰ���º���Գƴ���
//							else  if(LeftVal_B==RightVal_B)
//							{
//									LMR_State = 0; //��ͷ
//						  }
//				  }
//				  //�м�ǰ������û�д�������
//				 else  
//				  {
//						if(Trigger_Variables.Trigger_F==1)
//						{
//								Error = 0;
//			  				LMR_State = 1;      //����ֱ��
//						}
//						else if(Trigger_Variables.Trigger_B==1)
//						{
//			  				LMR_State = 0;    //��ͷ
//						}						
//					}	
//			}
				LastucRecSign = ucRecSign;
		}
  }		
}



#endif




