/*
 * ADC.c
 *
 * Created: 8/10/2025 5:26:21 PM
 *  Author: Mohammed Saeed
 */
#include "ADC.h"

void ADC_Init()
{
    // PORTA as Input and Disable Pull-up Resistors
	CLR_PORT(ADC_PORT);
	CLR_PORT(ADC_INPUT_PORT);
	//SET Vref =5V
	CLR_BIT(ADMUX,7);
	SET_BIT(ADMUX,6);

	//Prescaler ---> 8MHZ/64 >> F=125KHZ
	CLR_BIT(ADCSRA,0);
	SET_BIT(ADCSRA,1);
	SET_BIT(ADCSRA,2);
	/**********ADC RIGHT ADJUST RESULT ADMUX --> ADLAR********/
	CLR_BIT(ADMUX,5);
	/************TURN ON ENABLE BIT ADCSRA***************/
	SET_BIT(ADCSRA,7);
	CLR_BIT(ADCSRA,3); //for disable ADC Interrupt
}

u16 ADC_READ(u8 channel)
{    
	u16 ADC;
	 if(channel > 7)
	 {
		 return 0;
	 }
	//Select channel
	ADMUX &=0XE0; // BITS(5,6,7)

	ADMUX|=channel;
	
	//Conversion Delay and starting
	_delay_us(10);
	SET_BIT(ADCSRA,6);
	while(GET_BIT(ADCSRA,6));
	
	ADC =ADCL;
	ADC |= (ADCH <<8) ;
	return ADC;
}

f32 ADC_CALC_VOLT(u8 CH)
{   u16 ADC=ADC_READ(CH);
	f32 VOLT=(ADC*5.0)/1024.0;
	return VOLT;
}
