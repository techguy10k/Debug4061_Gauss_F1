#include "MricroStepDriver.h"
u8 rcr_remainder;   //ÖØ¸´¼ÆÊıÓàÊı²¿·Ö
u8 is_rcr_finish=1; //ÖØ¸´¼ÆÊıÆ÷ÊÇ·ñÉèÖÃÍê³É
long rcr_integer;	//ÖØ¸´¼ÆÊıÕûÊı²¿·Ö
long target_pos=0;  //ÓĞ·ûºÅ·½Ïò
long current_pos=0; //ÓĞ·ûºÅ·½Ïò
DIR_Type motor_dir=CW;//Ë³Ê±Õë
int PWM_Count_Set;
int flag = 0;// 0 OR 1
int mode = 0;// 0 OR 1
extern int stop;

/***************************************************
Name: TIM2_Startup
Tips:Double modes
***************************************************/
void TIM2_Startup(u32 frequency)   //Æô¶¯¶¨Ê±Æ÷8
{
	if(mode == 1)
	{
		if(frequency <=1)
		{
			HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
		}
		else
		{
			flag = 1;
			u16 temp_arr=1000000/frequency-1;
			if(stop == 0)
			HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
			htim2.Instance->ARR = temp_arr;
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,temp_arr/2);
				if(stop == 0)
			HAL_TIM_Base_Start_IT(&htim2);
		}		
	}
	else if( mode == 0)
	{
		if(frequency <=1)
		{
			HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
		}
		else
		{
			u16 temp_arr=1000000/frequency-1;
			HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
			htim2.Instance->ARR = temp_arr;
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,temp_arr/2);
		}		
	}
}

/***************************************************
Name: Motor Run Cycle
Tips:Stop it by setting 0 frequency
***************************************************/
void Locate_Run(DIR_Type dir,u32 frequency)
{
	mode=0;
	if(dir == 1)//Ë³Ê±Õë
		HAL_GPIO_WritePin(DIR__GPIO_Port,DIR__Pin,GPIO_PIN_RESET);
	else if(dir == 0)//ÄæÊ±Õë
		HAL_GPIO_WritePin(DIR__GPIO_Port,DIR__Pin,GPIO_PIN_SET);
	TIM2_Startup(frequency);	
}

/***************************************************
Name: Motor Run By Step
Tips:Before using again you have to set stop to 0
***************************************************/
void Locate_RunStep(DIR_Type dir,int times,u32 frequency)
{
	//ä¿®å¤è¾“å…¥è§’åº¦ä¸º0æ—¶ç–¯ç‹‚è½¬åŠ¨
	if(times==0)
	{
		times=1;
	}
	
	mode = 1;
	if(dir == 1)//Ë³Ê±Õë
		HAL_GPIO_WritePin(DIR__GPIO_Port,DIR__Pin,GPIO_PIN_RESET);
	else if(dir==0)//ÄæÊ±Õë
		HAL_GPIO_WritePin(DIR__GPIO_Port,DIR__Pin,GPIO_PIN_SET);
	PWM_Count_Set = times;
	if(flag == 0 && stop == 0)
	{
		TIM2_Startup(frequency);	
	}
}




//void Locate_Rle(long num,u32 frequency,DIR_Type dir) //Ïà¶Ô¶¨Î»º¯Êı
//{
//	if(num<=0) //ÊıÖµĞ¡µÈÓÚ0 ÔòÖ±½Ó·µ»Ø
//	{
//		printf("\r\nThe num should be greater than zero!!\r\n");
//		return;
//	}
//	if(TIM2->CR1&0x01)//ÉÏÒ»´ÎÂö³å»¹Î´·¢ËÍÍê³É  Ö±½Ó·µ»Ø
//	{
//		printf("\r\nThe last time pulses is not send finished,wait please!\r\n");
//		return;
//	}
//	if((frequency<20)||(frequency>100000))//Âö³åÆµÂÊ²»ÔÚ·¶Î§ÄÚ Ö±½Ó·µ»Ø
//	{
//		printf("\r\nThe frequency is out of range! please reset it!!(range:20Hz~100KHz)\r\n");
//		return;
//	}
//	motor_dir=dir;//µÃµ½·½Ïò	
//	DRIVER_DIR=motor_dir;//ÉèÖÃ·½Ïò
//	
//	if(motor_dir==CW)//Ë³Ê±Õë
//		target_pos=current_pos+num;//Ä¿±êÎ»ÖÃ
//	else if(motor_dir==CCW)//ÄæÊ±Õë
//		target_pos=current_pos-num;//Ä¿±êÎ»ÖÃ
//	
//	rcr_integer=num/(RCR_VAL+1);//ÖØ¸´¼ÆÊıÕûÊı²¿·Ö
//	rcr_remainder=num%(RCR_VAL+1);//ÖØ¸´¼ÆÊıÓàÊı²¿·Ö
//	is_rcr_finish=0;//ÖØ¸´¼ÆÊıÆ÷Î´ÉèÖÃÍê³É
//	TIM2_Startup(frequency);// ¿ªÆôTIM2
//}
///********************************************
////¾ø¶Ô¶¨Î»º¯Êı 
////num   -2147483648¡«2147483647
////frequency: 20Hz~100KHz
//*********************************************/
//void Locate_Abs(long num,u32 frequency)//¾ø¶Ô¶¨Î»º¯Êı
//{
//	if(TIM2->CR1&0x01)//ÉÏÒ»´ÎÂö³å»¹Î´·¢ËÍÍê³É Ö±½Ó·µ»Ø
//	{
//		printf("\r\nThe last time pulses is not send finished,wait please!\r\n");
//		return;
//	}
//	if((frequency<20)||(frequency>100000))//Âö³åÆµÂÊ²»ÔÚ·¶Î§ÄÚ Ö±½Ó·µ»Ø
//	{
//		printf("\r\nThe frequency is out of range! please reset it!!(range:20Hz~100KHz)\r\n");
//		return;
//	}
//	target_pos=num;//ÉèÖÃÄ¿±êÎ»ÖÃ
//	if(target_pos!=current_pos)//Ä¿±êºÍµ±Ç°Î»ÖÃ²»Í¬
//	{
//		if(target_pos>current_pos)
//			motor_dir=CW;//Ë³Ê±Õë
//		else
//			motor_dir=CCW;//ÄæÊ±Õë
//		DRIVER_DIR=motor_dir;//ÉèÖÃ·½Ïò
//		
//		rcr_integer=abs(target_pos-current_pos)/(RCR_VAL+1);//ÖØ¸´¼ÆÊıÕûÊı²¿·Ö
//		rcr_remainder=abs(target_pos-current_pos)%(RCR_VAL+1);//ÖØ¸´¼ÆÊıÓàÊı²¿·Ö
//		is_rcr_finish=0;//ÖØ¸´¼ÆÊıÆ÷Î´ÉèÖÃÍê³É
//		TIM2_Startup(frequency);//¿ªÆôTIM2
//	}
//}
