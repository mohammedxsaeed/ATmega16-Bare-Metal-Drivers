/*
 * LCD.c
 *
 * Created: 8/7/2025 9:02:50 PM
 *  Author: Mohammed Saeed
 */ 
#include "LCD.h"
#include <stdlib.h>


#if LCD_Mode == _8bit

static void LCD_CMD(u8 command)     //Rs = 0
{
	GPIO_WRITE_PIN(RSE_Port,RS,LOW);
	GPIO_WRITE_PORT(LCD_PORT,command);
	_delay_ms(1);
	GPIO_WRITE_PIN(RSE_Port,EN,HIGH);
	_delay_ms(1);
	GPIO_WRITE_PIN(RSE_Port,EN,LOW);
	_delay_ms(1);
}
void LCD_Print_Char(u8 data)  //Rs = 1
{
	GPIO_WRITE_PIN(RSE_Port,RS,HIGH);
	GPIO_WRITE_PORT(LCD_PORT,data);
	_delay_ms(1);
	GPIO_WRITE_PIN(RSE_Port,EN,HIGH);
	_delay_ms(1);
	GPIO_WRITE_PIN(RSE_Port,EN,LOW);
	_delay_ms(1);
	
}


void LCD_Init()
{
	 GPIO_PORT_Mode(LCD_PORT,OUTPUT);
	 GPIO_PORT_Mode(RSE_Port,OUTPUT);
	_delay_ms(50);
	LCD_CMD(0x38);   //Function Set 
	LCD_CMD(0x0E);   //Display ON / OFF
	LCD_CLEAR();
	LCD_CMD(0x06);   //Entry Mode Set
}

#elif LCD_Mode == _4bit

static void LCD_CMD(u8 command)     //Rs = 0
{
	GPIO_WRITE_PIN(RSE_Port,RS,LOW);
	GPIO_WRITE_PIN(LCD_PORT,7, GET_BIT(command,7)  );  // HIGHER Bits
	GPIO_WRITE_PIN(LCD_PORT,6,   GET_BIT(command,6) );
	GPIO_WRITE_PIN(LCD_PORT,5,   GET_BIT(command,5) );
	GPIO_WRITE_PIN(LCD_PORT,4, GET_BIT(command,4)   );
	_delay_ms(1);
	GPIO_WRITE_PIN(RSE_Port,EN,HIGH);
	_delay_ms(1);
	GPIO_WRITE_PIN(RSE_Port,EN,LOW);
	_delay_ms(1);
	GPIO_WRITE_PIN(LCD_PORT,7, GET_BIT(command,3) );    // LOWER bits
	GPIO_WRITE_PIN(LCD_PORT,6,  GET_BIT(command,2));
	GPIO_WRITE_PIN(LCD_PORT,5,  GET_BIT(command,1));
	GPIO_WRITE_PIN(LCD_PORT,4,   GET_BIT(command,0));
	_delay_ms(1);
	GPIO_WRITE_PIN(RSE_Port,EN,HIGH);
	_delay_ms(1);
	GPIO_WRITE_PIN(RSE_Port,EN,LOW);
	_delay_ms(1);
}
void LCD_Print_Char(u8 data)  //Rs = 1
{
	GPIO_WRITE_PIN(RSE_Port,RS,HIGH);
	GPIO_WRITE_PIN(LCD_PORT,7, GET_BIT(data,7)  );  // HIGHER Bits
	GPIO_WRITE_PIN(LCD_PORT,6, GET_BIT(data,6) );
	GPIO_WRITE_PIN(LCD_PORT,5, GET_BIT(data,5) );
	GPIO_WRITE_PIN(LCD_PORT,4, GET_BIT(data,4)   );
	_delay_ms(1);
	GPIO_WRITE_PIN(RSE_Port,EN,HIGH);
	_delay_ms(1);
	GPIO_WRITE_PIN(RSE_Port,EN,LOW);
	_delay_ms(1);
	GPIO_WRITE_PIN(LCD_PORT,7, GET_BIT(data,3)   );    // LOWER bits
	GPIO_WRITE_PIN(LCD_PORT,6, GET_BIT(data,2) );
	GPIO_WRITE_PIN(LCD_PORT,5, GET_BIT(data,1) );
	GPIO_WRITE_PIN(LCD_PORT,4, GET_BIT(data,0) );
	_delay_ms(1);
	GPIO_WRITE_PIN(RSE_Port,EN,HIGH);
	_delay_ms(1);
	GPIO_WRITE_PIN(RSE_Port,EN,LOW);
	_delay_ms(1);
	
}


void LCD_Init()
{
	GPIO_PORT_Mode(LCD_PORT,OUTPUT);
	GPIO_PORT_Mode(RSE_Port,OUTPUT);
	_delay_ms(50);
	LCD_CMD(0x02);
	LCD_CMD(0x28);   //Function Set
	LCD_CMD(0x0F);   //Display ON / OFF
	LCD_CLEAR();
	LCD_CMD(0x06);   //Entry Mode Set
	
	 
}

#endif


void LCD_Print_String(s8  * str)
{
	while(*str != '\0') 
	{
		LCD_Print_Char(*str);
		str++;
	}
}



void LCD_Printnum(s16 num )
{        
		char buffer[16];
		itoa(num,buffer,10);
		LCD_Print_String(buffer);
}
void LCD_GOTO(u8 ROW,u8 COL)
{  
	 _delay_ms(50);
    if (ROW == 0)
	{
		LCD_CMD(0x80+COL);    //Line 0
		
	}
	
	else if(ROW == 1)
	{
		LCD_CMD(0XC0+COL); 
		
}	
	LCD_CMD(0X0C);
}

void LCD_Print_Float(f32 num,u8 width,u8 precision)
{
	char buffer[16];
	dtostrf(num,width,precision,buffer);
	LCD_Print_String(buffer);
	
}

void LCD_CLRLOC( u8 ROW,u8 COL)
{
	LCD_GOTO(ROW,COL);
	for(int i=0;i<4;i++)
	{
		LCD_Print_Char(' ');
	}
	LCD_GOTO(ROW,COL);
}


void LCD_CLEAR()
{
	LCD_CMD(0x01);
	_delay_ms(2);
}


void LCD_CUSTOM_Char(u8 slot, const u8 * pattern) {
	// Only slots 0-7 are valid
	if(slot > 7) return;
	
	// Set CGRAM address command (01000000 = 0x40)
	LCD_CMD(0x40 | (slot << 3));
	
	// Write character pattern to CGRAM
	for (u8 i = 0; i < 8; i++) {
		LCD_Print_Char(pattern[i]);
	}
	
	// Return to DDRAM (display memory)
	LCD_CMD(0x80);
}