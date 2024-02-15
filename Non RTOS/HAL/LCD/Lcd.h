#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

#include <Dio.h>
#include <Dio_Cfg.h>
#include <Lcd_Cfg.h>

void Lcd_Init();
void Lcd_SendData(uint8);
void Lcd_SendCommand(uint8);

void Lcd_Char(uint8);
void Lcd_int(int32);
void Lcd_Clear();
void Lcd_String(char*);
void Lcd_SetCurse(uint8*,uint8*);

#endif /* HAL_LCD_LCD_H_ */
