#include "User_PID.h"
#include "math.h"
#include "MricroStepDriver.h"
static uint16_t x = 300; //74
static uint16_t y = 300; //64
extern int stop_flag;
float sx = 0, sy = 0;;
float PID_valueX=0;
float previous_errorX, previous_errorY,LastOut,diff;
int value =0;
int i=0;

int GetErrorX(void)
{
    return  Get_CoordinateXResult()-x;
}
void PIDOut(void)
{
		int change=0;
    float KpX =1.9, KiX = 0.002, KdX = 0.01;
    float errorX = 0,PX = 0, IX = 0., DX = 0;
    errorX = GetErrorX();
    PX = errorX;
    IX = IX + errorX;
    DX = errorX - previous_errorX;
    PID_valueX = (KpX * PX) + (KiX * IX) + (KdX * DX);

    previous_errorX = errorX;
//		if(PID_valueX>1000)
//			PID_valueX=1000;
//				if(PID_valueX<=-1000)
//			PID_valueX=-1000;
    //printf("X=%f\n",errorX);
		LastOut=PID_valueX;
		diff=PID_valueX-LastOut;
				
//	printf("x=%d,y=%d\n",Get_CoordinateXResult(),Get_CoordinateYResult());
	//__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,LastOut+diff)
        //ChannelOne_SetPositon(LastOut+diff);
	if(LastOut+diff>=0)
	{
		if(change==0)
		{
			HAL_Delay(1);
		}
	Locate_RunStep(0,LastOut+diff,500);
	change=1;
	}
	else
	{
		if(change==1)
		{
			HAL_Delay(1);
		}
	Locate_RunStep(0,LastOut+diff,500);
		change=0;
	}
	stop=0;
//printf("X=%f\n",LastOut+diff);
//    ChannelOne_SetPositon(0);
//    ChannelTwo_SetPositon(0);


}
void turn(void)
{
	if(stop_flag==0)
	{
		Locate_RunStep(1,800,100);
		if(Get_CoordinateXResult()>=295&&Get_CoordinateXResult()<305)
		{
			stop_flag=1;
			stop=0;
			flag=0;
			HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
			HAL_TIM_Base_Stop_IT(&htim2);
		}
	}
}
