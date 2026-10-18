
/*
 * LDR.c
 *
 * Created: 8/16/2025 3:28:26 PM
 *  Author: Mohammed Saeed
 */ 
#include "LDR.h"

f32 LDR_ReadPercent(u8 channel)
{
	f32 ADC_Val = ADC_READ(channel);
	return (ADC_Val * 100UL) / 1023.0; // Read Percent of Light Intensity
}
