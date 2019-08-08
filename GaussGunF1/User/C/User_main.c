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
//用户常量
extern const uint8_t LCDtable_NVIDIA[8][192];
uint16_t key=0x00;


void User_main(void)
{
	User_GetErrorUart_Init();
	User_DebugUart_Init();
	User_DistantUart_Init();
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	
	LCD_Init();
	

	while(1)
	{
		key = Key_scan();
		LCD_UpdateAllPixel((uint8_t*)LCDtable_NVIDIA);
//		HAL_Delay(1000);
		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_9);
	}
	
}