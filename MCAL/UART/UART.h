/*
 * UART.h
 *
 * Created: 8/15/2025 2:29:27 PM
 *  Author: Mohammed Saeed
 */ 


#ifndef UART_H_
#define UART_H_
#include "STD_TYPES.h"
#include "UTILS.h"
#include "MemMAP.h"

#define F_CPU 8000000UL
#define Baud_Rate 9600

/*******************Initiate UART Tx and Rx***********************/
void UART_Init();

// send any data from Master MC To any Rx
void UART_SendData(u8 data);

// Receive data from MC or Rx Pin 
u8 UART_Rx();

// Send String Function
void UART_SendString( u8 *str);

#endif /* UART_H_ */