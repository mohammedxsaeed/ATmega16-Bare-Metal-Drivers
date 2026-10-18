/*
 * EXT_Interrupt.h
 *
 * Created: 8/12/2025 10:18:17 PM
 *  Author: Mohammed Saeed
 */ 


#ifndef EXT_INTERRUPT_H_
#define EXT_INTERRUPT_H_
#include "MemMAP.h"   //--> #include <avr/io.h>
#include "UTILS.h"
#include "STD_TYPES.h"
#include <avr/interrupt.h>
/************MODE******************/
#define Falling_edge 0X02
#define Rising_edge 0X03
#define Low_lvl 0X00
#define Change 0X01
/**************PINS**************/
#define INT0_PIN 0
#define INT1_PIN 1
#define INT2_PIN 2
/*******************************/
void INTERRUPT_Init(u8 pin,u8 mode);



#endif /* EXT_INTERRUPT_H_ */