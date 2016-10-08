#include "control.h"
#include "sys.h"
#define Kp_L  140       //40   
#define Kp_R  100     //50   

//��������
extern u16 ucRecSign;
extern u8 LMR_State;        //����״̬����  0-���  1-�м� 2-�ұ�

extern u8 Error;            //ƫ��
extern u16 LastucRecSign;
extern u8 lr;
extern u8 stflag;


/****************************************
Brief: �������
**************************************/
void Motor_Clockwise(u16 duty)
{
	  if(duty>1000)
			duty = 1000;
		if(duty<400)
			duty = 400;
    TIM_SetCompare2(TIM4,duty);
}

	void Stop(void )
{
  TIM_SetCompare2(TIM4,0);
}

/****************************************
Brief: �������
***************************************/

void Steer_Control(void)
{
	u16  duty;
	
	if(lr == 2) //right  LMR_State == 2
	{
	    duty = 1650 -	Kp_R*Error;
	}
	else if(lr == 1)       //left  LMR_State == 0
	{
		duty =  1650 +	Kp_L*Error;
  }
   else 
	 {
		duty =  1650;
	 }
	 
	 if(duty >2000)
		 duty = 2000;
	 if(duty <1150)
		 duty = 1150;
	
	TIM_SetCompare1(TIM2,duty);    

}



/*

//����ٶȿ���

*/
void Motor_Control(void)
{
	
		  if(LastucRecSign)
			{
					stflag=1;
					if(lr == 0)			//ǰ			 LMR_State == 1
						Motor_Clockwise(1000);						
					else if(Error == 2)
						Motor_Clockwise(900);	
					else 
						Motor_Clockwise(830);
			}
	   
			else if(stflag)
			{
					//Stop();
					Motor_Clockwise(400);
			}
			else
			{
					Stop();
			}
	


}
