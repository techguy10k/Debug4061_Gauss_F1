#include "User_Check.h"
#include "LCD.h"
#include "KeyPad.h"
#include "GaussGun.h"

extern const uint8_t Basic1Table[];
extern const uint8_t Basic2Table[];
extern const uint8_t Basic3Table[];
extern const uint8_t Advance1Table[];
extern const uint8_t Advance2Table[];
extern const uint8_t ModeSetTable[];
extern const uint8_t Basic1FireTable[];


void DealBasic1(void);
void DealBasic2(void);
void DealBasic3(void);

void DealAdvance1(void);
void DealAdvance2(void);

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
	
}


void DealBasic3(void)
{
	
}


void DealAdvance1(void)
{
	
}


void DealAdvance2(void)
{
	
}

