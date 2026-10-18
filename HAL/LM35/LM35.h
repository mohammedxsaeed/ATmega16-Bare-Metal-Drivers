/*
 * LM35.h
 *
 * Created: 8/11/2025 7:01:12 PM
 *  Author: Mohammed Saeed
 */ 


#ifndef LM35_H_
#define LM35_H_
#include "ADC/ADC.h"

f32 LM35_CALC_TEMP(u8 CH);
f32 LM35_CALC_VOLT(u8 CH);


#endif /* LM35_H_ */