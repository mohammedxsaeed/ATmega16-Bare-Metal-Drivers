/*
 * DIO_Interface.c
 *
 * Created: 8/9/2025 12:08:28 PM
 *  Author: Mohammed Saeed
 */

#include "DIO.h"
/*****FUNCTIONS DECLARATIONS***********/

void GPIO_PIN_Mode(DIO_PORT_TYPE port,u8 PIN_Num, DIO_PIN_STATE State)
{
	switch(State)
	{
		case OUTPUT:
			switch(port)
			{
				case PA: SET_BIT(DDRA,PIN_Num); break;
				case PB: SET_BIT(DDRB,PIN_Num); break;
				case PC: SET_BIT(DDRC,PIN_Num); break;
				case PD: SET_BIT(DDRD,PIN_Num); break;
			} break;
		case INPUT:
			switch(port)
			{
				case PA: CLR_BIT(DDRA,PIN_Num); CLR_BIT(PORTA,PIN_Num); break;
				case PB: CLR_BIT(DDRB,PIN_Num); CLR_BIT(PORTB,PIN_Num); break;
				case PC: CLR_BIT(DDRC,PIN_Num); CLR_BIT(PORTC,PIN_Num); break;
				case PD: CLR_BIT(DDRD,PIN_Num); CLR_BIT(PORTD,PIN_Num); break;
			}break;
		case INPULL:
			switch(port)
			{
				case PA: CLR_BIT(DDRA,PIN_Num); SET_BIT(PORTA,PIN_Num); break;
				case PB: CLR_BIT(DDRB,PIN_Num); SET_BIT(PORTB,PIN_Num); break;
				case PC: CLR_BIT(DDRC,PIN_Num); SET_BIT(PORTC,PIN_Num); break;
				case PD: CLR_BIT(DDRD,PIN_Num); SET_BIT(PORTD,PIN_Num); break;
			}break;
	}
}
/************************************************************************/

void GPIO_WRITE_PIN(DIO_PORT_TYPE port,u8 PIN_Num, DIO_VOLT_STATE volt)
{
	switch(volt)
	{
		case HIGH:
		switch(port)
		{
			case PA: SET_BIT(PORTA,PIN_Num); break;
			case PB: SET_BIT(PORTB,PIN_Num); break;
			case PC: SET_BIT(PORTC,PIN_Num); break;
			case PD: SET_BIT(PORTD,PIN_Num); break;
		} break;
		case LOW:
		switch(port)
		{
			case PA: CLR_BIT(PORTA,PIN_Num); break;
			case PB: CLR_BIT(PORTB,PIN_Num); break;
			case PC: CLR_BIT(PORTC,PIN_Num); break;
			case PD: CLR_BIT(PORTD,PIN_Num); break;
		}break;
}
		}
/****************************************************/
void GPIO_TGL_PIN(DIO_PORT_TYPE port,u8 PIN_Num)
{
	switch(port)
	{
		case PA: TGL_BIT(PORTA,PIN_Num); break;
		case PB: TGL_BIT(PORTB,PIN_Num); break;
		case PC: TGL_BIT(PORTC,PIN_Num); break;
		case PD: TGL_BIT(PORTD,PIN_Num); break;
	}
}
/******************************************************/
void GPIO_PORT_Mode(DIO_PORT_TYPE port, DIO_PIN_STATE mode)
{
		switch(mode)
	{
		case OUTPUT:
		switch(port)
		{
			case PA: DDRA=0XFF; break;
			case PB: DDRB=0XFF; break;
			case PC: DDRC=0XFF; break;
			case PD: DDRD=0XFF; break;
		}break;

		case INPUT:
		switch(port)
		{
            case PA: DDRA=0X00; PORTA=0X00; break;
            case PB: DDRB=0X00; PORTB=0X00; break;
            case PC: DDRC=0X00; PORTC=0X00; break;
            case PD: DDRD=0X00; PORTD=0X00; break;
		}break;

		case INPULL:
		switch(port)
		{
			case PA: DDRA=0X00; PORTA=0XFF; break;
			case PB: DDRB=0X00; PORTB=0XFF; break;
			case PC: DDRC=0X00; PORTC=0XFF; break;
			case PD: DDRD=0X00; PORTD=0XFF; break;
		}
		break;
	}
		}



		void GPIO_WRITE_PORT(DIO_PORT_TYPE port, DIO_VOLT_STATE volt)
		{
				switch(volt)
				{
					case HIGH:
					switch(port)
					{
						case PA: PORTA=0XFF; break;
						case PB: PORTB=0XFF; break;
						case PC: PORTC=0XFF; break;
						case PD: PORTD=0XFF; break;
					}break;

					case LOW:
					switch(port)
					{
						case PA: PORTA=0X00; break;
						case PB: PORTB=0X00; break;
						case PC: PORTC=0X00; break;
						case PD: PORTD=0X00; break;
					}break;

		}
		}


			DIO_VOLT_STATE GPIO_READ_PIN(DIO_PORT_TYPE port,u8 PIN_Num)
			{
				DIO_VOLT_STATE Volt=LOW;
				switch(port)
				{
					case PA:
					Volt=GET_BIT(PINA,PIN_Num);
					break;
					case PB:
					Volt=GET_BIT(PINB,PIN_Num);
					break;
					case PC:
					Volt=GET_BIT(PINC,PIN_Num);
					break;
					case PD:
					Volt=GET_BIT(PIND,PIN_Num);
					break;

				}
				return Volt;
			}

			u8 GPIO_READ_PORT(DIO_PORT_TYPE port)
			{
				u8 PIN_PORT=0;
				switch(port)
				{
					case PA:
					PIN_PORT=PINA;
					break;
					case PB:
					PIN_PORT=PINB;
					break;
					case PC:
					PIN_PORT=PINC;
					break;
					case PD:
					PIN_PORT=PIND;
					break;

				}


				return PIN_PORT;
			}
