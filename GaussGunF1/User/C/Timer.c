#include "Timer.h"

int PWM_Count = 0;
extern int PWM_Count_Set;
int stop = 0;
extern int flag1;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if( htim == (&htim2) )
  {
    PWM_Count++;
		if(PWM_Count  == PWM_Count_Set && PWM_Count != 0 && PWM_Count_Set != 0 )
		{
			HAL_TIM_PWM_Stop(&htim2,TIM_CHANNEL_1);
//		HAL_TIM_Base_Stop(&htim2);
			flag = 0;
							if(flag1 == 0)
				flag1 = 1;
			else if(flag1 == 1)
				flag1 = 0;
			stop = 1;
//			flag1=-flag1;
			PWM_Count = 0;
			HAL_TIM_Base_Stop_IT(&htim2);
		}
  }
}

