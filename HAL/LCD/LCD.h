/*
 * LCD.h
 *
 * Created: 8/7/2025 9:03:01 PM
 *  Author: Mohammed Saeed
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "DIO/DIO.h"

#define		_4bit   1
#define		_8bit   2

#define		LCD_Mode   _4bit


#define EN			0
#define RS			1
#define RSE_Port	PB
#define LCD_PORT	PD
#define DIV   0

void LCD_Init();

void LCD_CLEAR();

void LCD_Print_Char(u8 data);

void LCD_Print_String(s8 * str);

void LCD_Printnum(s16 num );

void LCD_GOTO(u8 ROW,u8 COL);

void LCD_CLRLOC( u8 ROW,u8 COL);

void LCD_Print_Float(f32 num,u8 width,u8 precision);

void LCD_CUSTOM_Char(u8 slot, const u8 * pattern);

#endif /* LCD_H_ */