/*
 * MemMAP.h
 *
 * Created: 8/9/2025 11:57:16 AM
 *  Author: Mohammed Saeed
 */


#ifndef MEMMAP_H_
#define MEMMAP_H_
#include "STD_TYPES.h"

#define PINA  (*(volatile u8*)(0X39))
#define PINB  (*(volatile u8*)(0X36))
#define PINC  (*(volatile u8*)(0X33))
#define PIND  (*(volatile u8*)(0X30))
/***************************************/
#define DDRA  (*(volatile u8*)(0X3A))
#define DDRB  (*(volatile u8*)(0X37))
#define DDRC  (*(volatile u8*)(0X34))
#define DDRD  (*(volatile u8*)(0X31))
/***************************************/
#define PORTA (*(volatile u8*)(0X3B))
#define PORTB (*(volatile u8*)(0X38))
#define PORTC (*(volatile u8*)(0X35))
#define PORTD (*(volatile u8*)(0X32))
/****************ADC*******************/
#define ADMUX			( *(volatile u8 *) (0x27) )
#define ADCSRA			( *(volatile u8 *) (0x26) )
#define ADCH			( *(volatile u8 *) (0x25) )
#define ADCL			( *(volatile u8 *) (0x24) )

#define SFIOR			(*(volatile u8*)(0x50))
/****************TIMERS & INTERRUPTS*******************/
/// Timer 0
#define TCCR0   (*(volatile u8*)(0x53))
#define TCNT0   (*(volatile u8*)(0x52))
#define OCR0    (*(volatile u8*)(0x5C))

/// Timer 1
#define TCCR1A  (*(volatile u8*)(0x4F))
#define TCCR1B  (*(volatile u8*)(0x4E))
#define TCNT1   (*(volatile u16*)(0x4C))
#define OCR1A   (*(volatile u16*)(0x4A))
#define OCR1B   (*(volatile u16*)(0x48))
#define ICR1    (*(volatile u16*)(0x46))

/// Timer 2
#define TCCR2   (*(volatile u8*)(0x45))
#define TCNT2   (*(volatile u8*)(0x44))
#define OCR2    (*(volatile u8*)(0x43))
/****************************************/
/// Interrupt Registers
#define TIMSK   (*(volatile u8*)(0x59))
#define TIFR    (*(volatile u8*)(0x58))
#define SREG    (*(volatile u8*)(0x5F))

/* External Interrupt Registers */
#define MCUCR   (*(volatile u8*)(0x55))
#define MCUCSR  (*(volatile u8*)(0x54))
#define GICR    (*(volatile u8*)(0x5B))
#define GIFR    (*(volatile u8*)(0x5A))
/*************************************/
/* UART Registers */
#define UBRRH   (*(volatile u8*)(0x40))
#define UBRRL   (*(volatile u8*)(0x29))
#define UCSRA   (*(volatile u8*)(0x2B))
#define UCSRB   (*(volatile u8*)(0x2A))
#define UCSRC   (*(volatile u8*)(0x40))
#define UDR     (*(volatile u8*)(0x2C))


#endif /* MEMMAP_H_ */
