/*
 * KEYPAD.c
 *
 * Created: 8/8/2025 2:37:26 PM
 *  Author: Hassan-Hetta
 */ 


#include "KEYPAD.h"

void KEYPAD_Init()
{

	for(u8 i =0;i<4;i++)
	{
		GPIO_PIN_Mode(KEYPAD_PORT,FIRST_OUTPUT+i,OUTPUT);
		GPIO_PIN_Mode(KEYPAD_PORT,FIRST_INPUT+i,INPULL);
	}
	
}
u8 KEYPAD_getkey()
{
	u8 r,c,key=NO_KEY; 
	
	for(u8 i = 0;i<ROW;i++)
	{
		GPIO_WRITE_PIN(KEYPAD_PORT,FIRST_OUTPUT+i,HIGH);
	}
	
	for(r = 0;r<ROW;r++) // looping rows
	{
		GPIO_WRITE_PIN(KEYPAD_PORT,FIRST_OUTPUT+r,LOW);
		for(c=0;c<COL;c++)
		{
			if(GPIO_READ_PIN(KEYPAD_PORT,FIRST_INPUT+c)==LOW)
			{
				key = Key_array[r][c];
				
				while(GPIO_READ_PIN(KEYPAD_PORT,FIRST_INPUT+c)==LOW);
			}
		}
		GPIO_WRITE_PIN(KEYPAD_PORT,FIRST_OUTPUT+r,HIGH);
	}
	
	return key;
}

