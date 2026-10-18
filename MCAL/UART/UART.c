/*
 * UART.c
 *
 * Created: 8/15/2025
 * Author: Mohammed Saeed
 */ 
#include "UART.h"

void UART_Init(void)
{ 
    // SET Baud Rate and UBRR
    u16 UBRR = (F_CPU / (16UL * Baud_Rate)) - 1;
    UBRRH = (u8)(UBRR >> 8);
    UBRRL = (u8)UBRR;
    
    // Enable Normal Mode
    CLR_BIT(UCSRA, 1);
    
    // Enable USART Sender & Receiver
    SET_BIT(UCSRB, 3); //TXEN
    SET_BIT(UCSRB, 4); //RXEN
	
	CLR_BIT(UCSRB, 2);
	// Configure Frame: 8-data bits, 1 stop bit, No parity
	UCSRC = 0x86;
}

void UART_SendData(u8 data)
{
    // UDRE is Bit 5 in UCSRA
    while(!GET_BIT(UCSRA, 5));
    UDR = data;
}

u8 UART_Rx(void)
{
    // RXC is Bit 7 in UCSRA
    while(!GET_BIT(UCSRA, 7));
    return UDR;
}

void UART_SendString(u8 *str)
{
    while(*str != '\0')
    {
        UART_SendData(*str);
        str++;
    }
    UART_SendData('\n');
}