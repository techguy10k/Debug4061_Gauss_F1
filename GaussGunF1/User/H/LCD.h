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
#define u16 uint16_t
#define u32 uint32_t
#define u8 uint8_t
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
/* 写一定长度图像 */
void LCD_WriteLine(uint8_t* data,uint16_t size,uint8_t PosY,uint8_t PosX);
/* 清空屏幕 */
void LCD_Clear(void);
/* 显示8*8阿拉伯数字 */
void LCD_Display8_8Number(uint8_t number);
/* 打印8*8 正号 + */
void LCD_Display_Positive(void);
/* 打印8*8 负号 - */
void LCD_Display_Negative(void);
/*使用字库显示数字或者字符*/
void LCD_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size);
/*使用LCD显示一个点*/
void LCD_DrawPoint(uint8_t x,uint8_t y,uint16_t mode);
/*显示一个字符串*/
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);

#endif