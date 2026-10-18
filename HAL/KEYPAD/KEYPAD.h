/*
 * KEYPAD.h
 *
 * Created: 8/8/2025 2:37:41 PM
 *  Author: Hassan-Hetta
 */ 
#include "DIO/DIO.h"

#ifndef KEYPAD_H_
#define KEYPAD_H_


#define COL		4
#define ROW		4
#define NO_KEY  0
#define FIRST_OUTPUT  4
#define FIRST_INPUT   0
#define KEYPAD_PORT PC
static u8 Key_array [ROW][COL]={
	{'7','8' ,'9' ,'/' },
	{'4','5' ,'6' ,'*' },
	{'1','2' ,'3' ,'-'},
	{'c','0' ,'=' ,'+' },
};

void KEYPAD_Init();
u8 KEYPAD_getkey();






#endif /* KEYPAD_H_ */