#ifndef STEP_HH
#define STEP_HH
#include "sys.h"
#include "stdlib.h"	
#include <stdio.h>
#include "tim.h"
#include "Timer.h"
#include "gpio.h"
/********** ������ �˿ڶ��� **************
//DRIVER_DIR   PE0 
//DRIVER_OE    PE1 
//STEP_PULSE   PA5
(TIM2_CH2,LCD_RW)
******************************************/
#define DRIVER_DIR   PCout(0) // ��ת���� 
#define DRIVER_OE    PCout(2) // ʹ�ܽ� �͵�ƽ��Ч
#define RCR_VAL    255  //ÿ������RCR_VAL+1���Σ��ж�һ�Σ����ֵ��0~255�����ô�һЩ���Խ����ж�Ƶ��

typedef enum
{
	CW = 1,//�ߵ�ƽ˳ʱ��
	CCW = 0,//�͵�ƽ��ʱ��
}DIR_Type;//���з���

extern long target_pos;//�з��ŷ���
extern long current_pos;//�з��ŷ���
extern int PWM_Count_Set;
extern int flag;
extern int stop;

void Driver_Init(void);//��������ʼ��
void TIM2_OPM_RCR_Init(u16 arr,u16 psc);//TIM2_CH2 ���������+�ظ��������ܳ�ʼ��
void TIM2_Startup(u32 frequency);   //������ʱ��8
void Locate_Rle(long num,u32 frequency,DIR_Type dir); //��Զ�λ����
void Locate_Abs(long num,u32 frequency);//���Զ�λ����
void Locate_RunStep(DIR_Type dir,int times,u32 frequency);//Run_Step
void Locate_Run(DIR_Type dir,u32 frequency);//Run
#endif
