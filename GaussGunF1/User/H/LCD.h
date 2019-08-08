#ifndef LCD_H_
#define LCD_H_

//A4 RS 又叫A0
//A6 RST
//A1 CS

//SPI
//SCK  PA5
//MOSI PA7


#include "stdint.h"
#include "stm32f1xx_hal.h"

#include "main.h"
#include "spi.h"

/* LCD写命令 */
void LCD_WriteCommand(uint8_t Command);
/* LCD写数据 */
void LCD_WriteDdata(uint8_t Data);
/* LCD写列地址 */
void LCD_SetColumnAddress(uint8_t ColumnAddress);
/* LCD写页地址 */
void LCD_SetPageAddress(uint8_t PageAddress);
/* LCD设置数据指针位置 */
void LCD_SetPointerPositon(uint8_t PageAddress,uint8_t ColumnAddress);
/* LCD刷新一帧图片 */
void LCD_UpdateAllPixel(uint8_t* Address);
/* LCD初始化 */
void LCD_Init(void);









#endif