#include "User_JY901.h"

short CharToShort(unsigned char cData[]);

uint8_t _JY901_I2CRxBuffer[24] = {0};

 float Pitch_value = 0;
 float yaw_value = 0;
 float roll_value = 0;


void User_JY901_Init(void)
{
	HAL_I2C_Mem_Read_DMA(&hi2c1,0x50,0x34,I2C_MEMADD_SIZE_8BIT,_JY901_I2CRxBuffer,24);
}



void User_JY901_DMARx_CallBack(void)
{

	Pitch_value =  (float)CharToShort(&_JY901_I2CRxBuffer[18])/32768.0*180;         //转化后的角度值
	yaw_value =((float)CharToShort(&_JY901_I2CRxBuffer[20])/32768.0*180); 
	roll_value =((float)CharToShort(&_JY901_I2CRxBuffer[22])/32768.0*180); 	

	HAL_I2C_Mem_Read_DMA(&hi2c1,0x50,0x34,I2C_MEMADD_SIZE_8BIT,_JY901_I2CRxBuffer,24);
}



short CharToShort(unsigned char cData[])
{
	return ((short)cData[1]<<8)|cData[0];
}

