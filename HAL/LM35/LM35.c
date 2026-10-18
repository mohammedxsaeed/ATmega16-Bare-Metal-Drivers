/*
 * LM35.c
 *
 * Created: 8/11/2025 7:01:24 PM
 *  Author: Mohammed Saeed
 */ 
#include "LM35.h"

f32 LM35_CALC_TEMP(u8 CH)
{
	u16 ADC = ADC_READ(CH);
	// (ADC * 5.0 * 100) / 1024.0
	f32 temp = (ADC * 500.0) / 1024.0;
	return temp;
}

f32 LM35_CALC_VOLT(u8 CH)
{
	u16 ADC = ADC_READ(CH);
	f32 VOLT = (ADC * 5.0) / 1024.0;
	return VOLT;
}