#include "User_Check.h"
#include "LCD.h"
#include "KeyPad.h"
#include "GaussGun.h"
#include "MricroStepDriver.h"
#include "User_Uart.h"
#include "math.h"

#include "tim.h"

extern int stop_flag;
extern float  _GetDistantResults;
uint16_t timers1=0;
float Speed=0,BulletMomentum=0,cnt;
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
extern float _GetDistantResults;

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
	
	
	//LCD_WriteLine((uint8_t*)ModeSetTable,20,0,0);
	LCD_ShowString(0,0,192,12,12,"Please select mode");
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
				DealBasic2();
			}
			else if(KeyPressVal == 4)
			{
			  DealBasic2();
			}
			else if(KeyPressVal == 5)
			{
				DealBasic2();
			}
		}
	}
	
}


void DealBasic1(void)
{
__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,2500);
	HAL_Delay(2000);
	//LCD_Clear();
}
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//	if(GPIO_Pin==SpeedInput_Pin)
//	{
//		TIM4->CNT=0;
//		HAL_TIM_Base_Start(&htim4);
//		
//		while(TIM4->CNT<=50)
//		{}
//		
//		while((HAL_GPIO_ReadPin(SpeedInput_GPIO_Port,SpeedInput_Pin) == GPIO_PIN_SET) && (TIM4->CNT<=65500))
//		{
//		}
//		HAL_TIM_Base_Stop(&htim4);
//		timers1=TIM4->CNT;
//	}
//}
	
void DealBasic2(void)
{
	volatile double Distant = 0; 
	double temp,xxx;
	LCD_Clear();
	HAL_Delay(10);
	LCD_ShowString(0,0,168,12,12,"Base 2 Distant");
	LCD_ShowString(0,20,168,24,12,"Please ready for speed input");
	temp= DigitDialIn();
	Distant += temp;
	LCD_ShowNum(0,32,temp,1,16);
	LCD_ShowChar(16,32,'.',16);
	temp= DigitDialIn();
	Distant += temp / 10;
	LCD_ShowNum(32,32,temp,1,16);
	temp= DigitDialIn();
	Distant += temp / 100;
	LCD_ShowNum(48,32,temp,1,16);
//	
//	
	while(Key_scan() != 0);	
	while(Key_scan() == 0);
  //HAL_EXTI_ClearPending();
  //HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	//y = -234.78x5 + 6154.6x4 - 64299x3 + 334512x2 - 866729x + 898922

	//GaussGun_Fire((-Distant+11.096)/0.0017);
	
	GaussGun_Fire(-170.7*pow(Distant,3) + 2556.1*pow(Distant,2) - 13083*Distant + 26492);
	
//	xxx=-170.7*pow(Distant,3) + 2556.1*pow(Distant,2) - 13083*Distant + 26492;
//	
//	LCD_Output_Float(0,0,"time",xxx);
//	LCD_Output_Float(16,0,"speed",Distant);
	//GaussGun_Fire(4000);
	//DistantFire(Distant);
	//y = -0.0017x + 11.096
	//HAL_TIM_Base_Start(&htim4);
	//TIM4->CNT=0;
	while(1)
	{
		if(HAL_GPIO_ReadPin(speedinput_GPIO_Port,speedinput_Pin)==GPIO_PIN_RESET)
		{
			HAL_TIM_Base_Init(&htim5);
			TIM4->CNT=0;
			HAL_TIM_Base_Start(&htim4);
			break;
		}
	}
	//while((HAL_GPIO_ReadPin(speedinput_GPIO_Port,speedinput_Pin)==GPIO_PIN_SET)&&TIM4->CNT<65500);
	
	while((HAL_GPIO_ReadPin(speedinput_GPIO_Port,speedinput_Pin)==GPIO_PIN_RESET)&&TIM4->CNT<65500)
	{}
	cnt=(float)TIM4->CNT;
	HAL_TIM_Base_Stop(&htim4);
	LCD_Clear();
	//if(TIM4->CNT>=65499)
	//LCD_Output_Float(0,0,"cnt",TIM4->CNT);
	//while(1);
	BulletSpeed();
	//LCD_Clear();
	//while(1);、
	
	HAL_Delay(500);
	FinalMomentum();
	
	HAL_Delay(5000);
	while(1);
	LCD_Clear();
	HAL_Delay(2000);
	NVIC_SystemReset();
	
}
void BulletSpeed(void)
{
	float BulletLong=0.024,BulletMass=0.01135;
	LCD_Clear();
	Speed=BulletLong/((float)cnt/1000000.0);
	BulletMomentum=(Speed)*BulletMass;
//	LCD_Output_Float(0,0,"buttle speed",Speed);
//	LCD_Output_Float(0,16,"Momentum",BulletMomentum);
	//HAL_TIM_Base_Stop(&htim4);
	TIM4->CNT=0;
	//HAL_TIM_Base_Stop(&htim4);
//	LCD_ShowNum(0,0,(int)Speed,5,16);
//	LCD_ShowNum(0,16,(int)TIM4->CNT,5,16);
}
void FinalMomentum(void)
{
	float x1,x2,LastSpeed,cut;
	float CarMass=0.18996+0.01135,CarMomentum;
	x1=_GetDistantResults;
	HAL_Delay(1000);
	x2=_GetDistantResults;
	LastSpeed=(x1-x2)/(1000/1000);
	CarMomentum=CarMass*LastSpeed;
	LCD_Clear();
	HAL_Delay(2000);
	LCD_Output_Float(0,0,"Car Speed",LastSpeed);
	LCD_Output_Float(0,16,"Car Momentum",CarMomentum);
	LCD_Output_Float(0,32,"buttle speed",Speed);
	LCD_Output_Float(0,48,"Momentum",BulletMomentum);
	HAL_Delay(10000);
	LCD_Clear();
	HAL_Delay(2000);
	cut=((BulletMomentum-CarMomentum)/BulletMomentum)*100;
	LCD_Output_Float(0,0,"difference",cut);
//	LCD_ShowString(0,0,168,12,16,"Car SpeedC,ar Speed ");
//	LCD_ShowNum(80,0,LastSpeed,5,16);
//	LCD_ShowString(0,16,168,12,16,"Car Momentum ");
//	LCD_ShowNum(130,16,(int)CarMomentum,5,16);
//	LCD_ShowNum(00,24,(int)x1,5,24);
//	LCD_ShowNum(00,48,(int)x2,5,24);
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
	Angle += DigitDialIn() * 10;
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
		Locate_RunStep(1,(uint16_t)(8.2*Angle),100);
	}
	else
	{
		stop = 0;
		Locate_RunStep(0,(uint16_t)(8.2*abs(Angle)),100);		
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
	
//	if(distant_cm > 300)
//	{
//		distant_cm = 300;
//	}
//	if(distant_cm < 200)
//	{
//		distant_cm = 200;
//	}
	
	// = (uint16_t)((-5.4257*distant_cm + 2663.7) * 1.2);
	//__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,Set_PWM);
	//HAL_Delay(1000);
	GaussGun_Fire(-0.0017*distant_cm + 11.096);

}


void AutoTurnFire(void)
{
	volatile float distant = 0;
	
	while(stop_flag==0)
	{
		Locate_RunStep(1,1000,50);
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
	
}
