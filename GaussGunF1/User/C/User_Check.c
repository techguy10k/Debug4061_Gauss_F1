#include "User_Check.h"
#include "LCD.h"
#include "KeyPad.h"
#include "GaussGun.h"
#include "MricroStepDriver.h"
#include "User_Uart.h"

#include "tim.h"

int adv2=0;
extern int stop_flag;
extern float  _GetDistantResults;
int flag1=0;
int stop_flag0=0;
int stop_flag1=0;

extern const uint8_t Basic1Table[];
extern const uint8_t Basic2Table[];
extern const uint8_t Basic3Table[];
extern const uint8_t Advance1Table[];
extern const uint8_t Advance2Table[];
extern const uint8_t ModeSetTable[];
extern const uint8_t Basic1FireTable[];
extern const uint8_t Basic2PleaseInputTable[];
extern const uint8_t Basic2DistantDisplay[];
extern const uint8_t Basic3InputAngleTable[];
extern const uint8_t Basic3InputDistantTable[];

void DistantFire(uint16_t distant_cm);

void DealBasic1(void);
void DealBasic2(void);
void DealBasic3(void);

void DealAdvance1(void);
void DealAdvance2(void);
void AutoTurnFire(void);

uint8_t DigitDialIn(void);

void Check(void)
{
	uint16_t KeyPressVal = 0;
	
	
	LCD_WriteLine((uint8_t*)ModeSetTable,20,0,0);
	//有按键按下
	if(Key_scan() != 0x00)
	{
		//消抖
		HAL_Delay(100);
		if(Key_scan() != 0x00)
		{
			KeyPressVal = Key_scan();
			
			if(KeyPressVal == 1)
			{
				DealBasic1();
			}
			else if(KeyPressVal == 2)
			{
				DealBasic2();
			}
			else if(KeyPressVal == 3)
			{
				DealBasic3();
			}
			else if(KeyPressVal == 4)
			{
			  DealAdvance1();
			}
			else if(KeyPressVal == 5)
			{
				DealAdvance2();
			}
		}
	}
	
}


void DealBasic1(void)
{
	LCD_Clear();
	HAL_Delay(10);
	LCD_WriteLine((uint8_t*)Basic1Table,12,0,0);
	LCD_WriteLine((uint8_t*)Basic1FireTable,21,1,0);
	while(Key_scan() != 0);	
	while(Key_scan() == 0);
	GaussGun_Fire(4350);
	HAL_Delay(2000);
	LCD_Clear();
}

void DealBasic2(void)
{
	volatile uint16_t Distant = 0; 
	
	LCD_Clear();
	HAL_Delay(10);
	LCD_WriteLine((uint8_t*)Basic2Table,15,0,0);
	LCD_WriteLine((uint8_t*)Basic2PleaseInputTable,30,1,0);
	
	
	Distant += DigitDialIn() * 100;
	Distant += DigitDialIn() * 10;
	Distant += DigitDialIn();
	
	LCD_WriteLine((uint8_t*)Basic2DistantDisplay,10,2,0);
	LCD_Display8_8Number(Distant / 100);
	LCD_Display8_8Number(Distant % 100 / 10);
	LCD_Display8_8Number(Distant % 10);
	
	LCD_WriteLine((uint8_t*)Basic1FireTable,21,3,0);
	
	while(Key_scan() != 0);	
	while(Key_scan() == 0);

	DistantFire(Distant);
	
	LCD_Clear();
	HAL_Delay(2000);
	
	
}


void DealBasic3(void)
{
	volatile uint16_t Distant = 0;
	volatile int16_t Angle = 0;
	volatile uint8_t KeyVal_Pos_Or_Neg = 0;
	volatile uint8_t KeyVal = 0;
	
	LCD_Clear();
	HAL_Delay(10);
	LCD_WriteLine((uint8_t*)Basic3Table,23,0,0);
	LCD_WriteLine((uint8_t*)Basic3InputAngleTable,20,1,0);
	
	while(Key_scan() != 0);
	while(Key_scan() == 0);
	
	KeyVal_Pos_Or_Neg = Key_scan();
	if((KeyVal_Pos_Or_Neg != 4) && (KeyVal_Pos_Or_Neg != 8))
	{
		LCD_Clear();
		HAL_Delay(10);
		return;
	}
	
	if(KeyVal_Pos_Or_Neg == 4)
	{
		LCD_Display_Positive();
	}
	else if(KeyVal_Pos_Or_Neg == 8)
	{
		LCD_Display_Negative();
	}
	
	Angle += DigitDialIn() * 10;
	Angle += DigitDialIn() * 1;
	if(KeyVal_Pos_Or_Neg == 8)
	{
		Angle = -Angle;
	}
	
	if(Angle > 30)
	{
		Angle = 30;
	}
	
	if(Angle < -30)
	{
		Angle = -30;
	}
	
	LCD_Display8_8Number(Angle / 10);
	LCD_Display8_8Number(Angle % 10);

	LCD_WriteLine((uint8_t*)Basic3InputDistantTable,22,2,0);
	Distant += DigitDialIn() * 100;
	Distant += DigitDialIn() * 10;
	Distant += DigitDialIn();
	
	LCD_Display8_8Number(Distant / 100);
	LCD_Display8_8Number(Distant % 100 / 10);
	LCD_Display8_8Number(Distant % 10);
	
	LCD_WriteLine((uint8_t*)Basic1FireTable,21,3,0);
	
	while(Key_scan() != 0);	
	while(Key_scan() == 0);

	//执行部分
	
	if(Angle > 0)
	{
		stop = 0;
		Locate_RunStep(1,(uint16_t)(16*Angle),100);
//		HAL_Delay(30000);
//					HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
//			HAL_TIM_Base_Stop_IT(&htim2);
	}
	else
	{
		stop = 0;
		Locate_RunStep(0,(uint16_t)(16*abs(Angle)),100);
//		HAL_Delay(30000);
//					HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
//			HAL_TIM_Base_Stop_IT(&htim2);		
		
	}
	HAL_Delay(5000);
	DistantFire(Distant);
	
	LCD_Clear();
	HAL_Delay(2000);
	
	
	

	
}


void DealAdvance1(void)
{
	int16_t StepCounter = 0;
	
	LCD_Clear();
	HAL_Delay(10);
	LCD_WriteLine((uint8_t*)Advance1Table,23,0,0);
	LCD_WriteLine((uint8_t*)Basic1FireTable,21,1,0);
	//等待按键按下
	while(Key_scan() != 0);	
	while(Key_scan() == 0);	
	
	stop_flag = 0;
	AutoTurnFire();
	HAL_Delay(2000);
}



void DealAdvance2(void)
{
	volatile float Set_PWM;
	LCD_Clear();
	
//	while(Key_scan() != 0);	
	//	while(Key_scan() == 0);	
	Set_PWM = (uint16_t)(-105.83*2.5 + 1324.2);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,Set_PWM);
	
while(1)
{

			if(flag==0)
	{
		HAL_Delay(200);
		stop=0;
	}
	Locate_RunStep(flag1,960,100);
	if(stop_flag1==0)
	{
	if(Get_CoordinateXResult()>290&&Get_CoordinateXResult()<=310)
	{
		HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_10);
		GaussGun_Fire(4350);
		stop_flag1=1;
	}
	}
	else
	{
		
	}
}
	
}


uint8_t DigitDialIn(void)
{
	int16_t Digit = 0;
	
	while(Key_scan() != 0);
	while(Key_scan() == 0);
	
	Digit = Key_scan();
	
	if(Digit == 1)
	{
		HAL_Delay(500);
		return 1;
	}
	else if(Digit == 2)
	{
		HAL_Delay(500);
		return 2;
	}
	else if(Digit == 3)
	{
		HAL_Delay(500);
		return 3;
	}
	else if(Digit == 5)
	{
		HAL_Delay(500);
		return 4;
	}
	else if(Digit == 6)
	{
		HAL_Delay(500);
		return 5;
	}
	else if(Digit == 7)
	{
		HAL_Delay(500);
		return 6;
	}
	else if(Digit == 9)
	{
		HAL_Delay(500);
		return 7;
	}
	else if(Digit == 10)
	{
		HAL_Delay(500);
		return 8;
	}
	else if(Digit == 11)
	{
		HAL_Delay(500);
		return 9;
	}
	else if(Digit == 14)
	{
		HAL_Delay(500);
		return 0;
	}

	HAL_Delay(500);
	return 0;
	
}

void DistantFire(uint16_t distant_cm)
{
	volatile uint16_t Set_PWM = 0;
	volatile uint16_t Set_UsTIME=0;
	if(distant_cm > 300)
	{
		distant_cm = 300;
	}
	if(distant_cm < 200)
	{
		distant_cm = 200;
	}
	if(distant_cm>250)
	{
	Set_PWM = (uint16_t)(-105.83*distant_cm/100 + 1324.2);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,Set_PWM);
	HAL_Delay(1000);
	GaussGun_Fire(4350);
	}
	else if(distant_cm<=250)
	{
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,1200);
		HAL_Delay(1000);
		Set_UsTIME=(uint16_t)(803.2*distant_cm/100 + 2367.9);
		GaussGun_Fire(Set_UsTIME);
	}
	

}


void AutoTurnFire(void)
{
	volatile float distant = 0;
	
	//flag1=1;
	while(stop_flag0==0)
	{
		Locate_RunStep(flag,480,500);
		HAL_Delay(3000);
		stop=0;
		//flag=0;
		
	while(stop_flag==0)
	{
		//last_flag=flag1;
		Locate_RunStep(flag1,960,100);
		if(flag==0)
		{
			HAL_Delay(200);
			stop=0;
		}
		if(Get_CoordinateXResult()>=295&&Get_CoordinateXResult()<305)
		//if(_GetDistantResults < 3.40)
		{
			stop_flag=1;
			stop=0;
			flag=0;
			HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
			HAL_TIM_Base_Stop_IT(&htim2);
		}
		
	}
	
	HAL_Delay(2000);
	distant = _GetDistantResults - 0.30;
	DistantFire((uint16_t)(distant * 100));
	HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_10);
	stop_flag0=1;
}
	
	
}
