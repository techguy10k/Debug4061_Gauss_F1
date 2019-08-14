#include "User_main.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

//自动生成文件
#include "usart.h"
#include "tim.h"

//用户头文件
#include "LCD.h"
#include "User_Uart.h"
#include "User_PID.h"
#include "KeyPad.h"
#include "GaussGun.h"
#include "User_Check.h"
#include "MricroStepDriver.h"
#include "User_JY901.h"

//用户函数


//用户常量
extern const uint8_t LCDtable_NVIDIA[8][192];
//用户变量
int16_t d233 = 0;
int stop_flag=0;

void User_main(void)
{
	int i=0;
	User_GetErrorUart_Init();
	User_DebugUart_Init();
	User_DistantUart_Init();
	//User_JY901_Init();
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	LCD_Init();
	LCD_UpdateAllPixel((uint8_t*)LCDtable_NVIDIA);
	HAL_Delay(3000);
	
	/* 让屏幕全白 */
	LCD_Clear();

	while(1)
	{
//		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,500);
//		HAL_Delay(2000);
//		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,2500);
//		HAL_Delay(2000); 
		
			
//		stop = 0;
//		Locate_RunStep(1,800,500);
//		HAL_Delay(4000);
//		stop = 0;
//		Locate_RunStep(0,800,500);
		//HAL_Delay(1000);

		//AutoTurnFire();
		DealAdvance2();

		//Check();
//		d233 = Get_CoordinateXResult();
		//turn();
		//while(1);
	}
	
}



