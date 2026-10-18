/*
 * DIO_interface.h
 *
 * Created: 8/9/2025 12:08:10 PM
 *  Author: Mohammed Saeed
 */


#ifndef DIO_H_
#define DIO_H_
/***********DEFINES&INCLUDES LIB**********/
#define F_CPU 8000000UL
#include <util/delay.h>
#include "STD_TYPES.h"
#include "UTILS.h"
#include "MemMAP.h"
/************PORTS ABS******************************/

typedef enum {
	PA,
	PB,
	PC,
	PD
	}DIO_PORT_TYPE;

	typedef enum {
		OUTPUT,
		INPUT,
		INPULL
	}DIO_PIN_STATE;

	typedef enum {
			LOW,
			HIGH
		}DIO_VOLT_STATE;
/*************FUNCTIONS PROTOTYPING*****************/

 /*******************PIN Mode Select******************/
		/* State : INPUT - INPULL - OUTPUT
		   Port : PA - PB - PC - PD
		   PIN  : 0 -> 7
		  */

void GPIO_PIN_Mode(DIO_PORT_TYPE port,u8 PIN_Num, DIO_PIN_STATE State);


 /*******************WRITE PIN******************/
		/* Volt : HIGH - LOW
		   Port : PA - PB - PC - PD
		   PIN  : 0 -> 7
		  */
void GPIO_WRITE_PIN(DIO_PORT_TYPE port,u8 PIN_Num, DIO_VOLT_STATE volt);

/****************Select Bit in a Microcontroller TO Toggle It**********/
/*
 Port : PA - PB - PC - PD
 PIN_Num  : 0 -> 7
 */

void GPIO_TGL_PIN(DIO_PORT_TYPE port,u8 PIN_Num);


 /*******************PORT Mode Select******************/
		/* Mode : INPUT - INPULL - OUTPUT
		   Port : PA - PB - PC - PD ---. DDRA , ARRC
		  */


void GPIO_PORT_Mode(DIO_PORT_TYPE port, DIO_PIN_STATE mode);

	/*******************WRITE PORT******************/
		/* Volt : HIGH - LOW
		   Port : PA - PB - PC - PD

		  */
void GPIO_WRITE_PORT(DIO_PORT_TYPE port, DIO_VOLT_STATE volt);

/*******READ PIN************/
/*
PORT :  PA - PB - PC - PD
 PIN  : 0 -> 7
 */
DIO_VOLT_STATE GPIO_READ_PIN(DIO_PORT_TYPE port,u8 PIN_Num);


/******READ Whloe  Data PORT***********/
/*
PORT :  PA - PB - PC - PD
*/

u8 GPIO_READ_PORT(DIO_PORT_TYPE port);

#endif /* DIO_H_ */
