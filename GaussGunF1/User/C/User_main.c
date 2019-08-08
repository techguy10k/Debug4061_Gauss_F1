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
#include "KeyPad.h"
#include "GaussGun.h"

//用户函数

/* 评委验收函数 */
void Check(void);

//用户常量
extern const uint8_t LCDtable_NVIDIA[8][192];
extern const uint8_t Basic1Table[];
extern const uint8_t Basic2Table[];
extern const uint8_t Basic3Table[];
extern const uint8_t Advance1Table[];
extern const uint8_t Advance2Table[];
//用户变量
uint16_t key=0x00;


void User_main(void)
{
	User_GetErrorUart_Init();
	User_DebugUart_Init();
	User_DistantUart_Init();
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	LCD_Init();
	LCD_UpdateAllPixel((uint8_t*)LCDtable_NVIDIA);
	HAL_Delay(1000);
	
	/* 让屏幕全白 */
	LCD_SetPointerPositon(0,0);
	for(uint16_t Counter = 0;Counter < 1536;Counter ++)
	{
		LCD_WriteDdata(0x00);
	} 
	LCD_SetPointerPositon(0,0);

	

	while(1)
	{
		Check();
//		key = Key_scan();		
//		if(key == 2)
//		{
//			GaussGun_Fire(5000);
//			HAL_Delay(3000);			
//		}	
		
		
		
	}
	
}


void Check(void)
{
	LCD_WriteLine((uint8_t*)Basic1Table,12,0,0);
	HAL_Delay(2000);
	
	/* 让屏幕全白 */
	LCD_SetPointerPositon(0,0);
	for(uint16_t Counter = 0;Counter < 1536;Counter ++)
	{
		LCD_WriteDdata(0x00);
	} 
	LCD_SetPointerPositon(0,0);	
	
	LCD_WriteLine((uint8_t*)Basic2Table,15,0,0);
	HAL_Delay(2000);
	
	/* 让屏幕全白 */
	LCD_SetPointerPositon(0,0);
	for(uint16_t Counter = 0;Counter < 1536;Counter ++)
	{
		LCD_WriteDdata(0x00);
	} 
	LCD_SetPointerPositon(0,0);

	LCD_WriteLine((uint8_t*)Basic3Table,23,0,0);
	HAL_Delay(2000);
	
	/* 让屏幕全白 */
	LCD_SetPointerPositon(0,0);
	for(uint16_t Counter = 0;Counter < 1536;Counter ++)
	{
		LCD_WriteDdata(0x00);
	} 
	LCD_SetPointerPositon(0,0);
	LCD_WriteLine((uint8_t*)Advance1Table,23,0,0);
	HAL_Delay(2000);


	/* 让屏幕全白 */
	LCD_SetPointerPositon(0,0);
	for(uint16_t Counter = 0;Counter < 1536;Counter ++)
	{
		LCD_WriteDdata(0x00);
	} 
	LCD_SetPointerPositon(0,0);
	LCD_WriteLine((uint8_t*)Advance2Table,22,0,0);
	HAL_Delay(2000);
	
	LCD_SetPointerPositon(0,0);
	for(uint16_t Counter = 0;Counter < 1536;Counter ++)
	{
		LCD_WriteDdata(0x00);
	} 

	
}

