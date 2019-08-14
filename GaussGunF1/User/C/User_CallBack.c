#include "User_CallBack.h"

#include "User_Check.h"
//私有函数申明


//公有远程变量申明
extern uint8_t _GetErrorRXBuffer[7];
extern int adv2;

/* 串口总回调函数 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	
	/* 串口3中断部分 */
	if(huart->Instance == USART3)
	{
		_GetCommandUartCallBack();
	}
	
	/* 串口1中断部分 */
	if(huart->Instance == USART1)
	{
		_GetErrorUartCallBack();
		if(adv2==1)
		{
			if(Get_CoordinateXResult()>295&&Get_CoordinateXResult()<300)
			{
				AutoTurnFire();
			}
		}
		//User_NewDistantUart_Init();
	}
	
	/* 串口2中断部分 */
	if(huart->Instance == USART2)
	{
		_GetDistantUartCallBack();
	}

	
}


///* I2C 总回调函数 */
//void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c)
//{
//	if(hi2c->Instance == I2C1)
//	{
//		User_JY901_DMARx_CallBack();
//	}
//}


