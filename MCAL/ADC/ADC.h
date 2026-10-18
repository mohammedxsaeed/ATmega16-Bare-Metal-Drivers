/*
 * ADC.h
 *
 * Created: 8/10/2025 5:26:11 PM
 *  Author: Mohammed Saeed
 */


#ifndef ADC_H_
#define ADC_H_
/********************************************/
#define F_CPU	8000000UL
#include <util/delay.h>
#include "STD_TYPES.h"
#include "UTILS.h"
#include "MemMAP.h"   //--> #include <avr/io.h>
/********************************************/
//initialization of ADC PORTA
#define ADC_PORT		DDRA
#define ADC_INPUT_PORT  PORTA
void ADC_Init();

// READ FROM  ADC Channel From PORTA (0 --> 7)
u16 ADC_READ(u8 channel);

// Calc input voltage from ADC <= 5V
f32 ADC_CALC_VOLT(u8 CH);

#endif /* ADC_H_ */