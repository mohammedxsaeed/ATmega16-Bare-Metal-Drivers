/*
 * Timer.c
 *
 * Created: 8/16/2025
 * Author: Mohammed Saeed
 */

#include "Timer.h"

/*******************  TIMER 0 *******************/

void Timer0_Init(Timer_Mode_t mode, u8 prescaler)
{
   
    // Reset Timer0 Control Register
    TCCR0 = 0;

    switch(mode)
    {
        case TIMER_NORMAL_MODE:
            CLR_BIT(TCCR0, 6); // WGM00
            CLR_BIT(TCCR0, 3); // WGM01
            SET_BIT(TIMSK, 0); // Enable TOIE0
            break;

        case TIMER_CTC_MODE:
            CLR_BIT(TCCR0, 6); // WGM00
            SET_BIT(TCCR0, 3); // WGM01
            SET_BIT(TIMSK, 1); // Enable OCIE0
            break;

        case TIMER_FAST_PWM:
            SET_BIT(TCCR0, 6); // WGM00
            SET_BIT(TCCR0, 3); // WGM01
            SET_BIT(TCCR0, 5); // COM01
            CLR_BIT(TCCR0, 4); // COM00
            SET_BIT(DDRB, 3);
			break;

        case TIMER_PWM_PHASE_CORRECT:
            SET_BIT(TCCR0, 6); // WGM00
            CLR_BIT(TCCR0, 3); // WGM01
            SET_BIT(TCCR0, 5); // COM01
            CLR_BIT(TCCR0, 4); // COM00
           SET_BIT(DDRB, 3);
		    break;
    }

    // Set Prescaler
    TCCR0 |= prescaler;
}

void Timer0_SetCompareValue(u8 value) {
    OCR0 = value;
}

void Timer0_SetCounter(u8 value) {
    TCNT0 = value;
}

void Timer0_Stop(void) {
    // Clear clock source bits (stop timer)
    TCCR0 &= 0xF8; // 0xF8 = 0b11111000
}


/******************* TIMER 1********************/

void Timer1_Init_Normal(u8 prescaler)
{
    TCCR1A = 0;
    TCCR1B = 0;

    // Set Prescaler
    TCCR1B |= prescaler;

    // Enable TOIE1
    SET_BIT(TIMSK, 2);
}

void Timer1_ICU_Init(ICU_Edge_t edge)
{
    // Edge Select
    if(edge == RISING_EDGE)
        SET_BIT(TCCR1B, 6); //ICES1
    else
        CLR_BIT(TCCR1B, 6); //ICES1

    // Enable Input Capture Interrupt
    SET_BIT(TIMSK, 5);//TICIE1
}

void Timer1_ICU_SetEdge(ICU_Edge_t edge)
{
    if(edge == RISING_EDGE)
        SET_BIT(TCCR1B, 6);
    else
        CLR_BIT(TCCR1B, 6);
}

u16 Timer1_ICU_GetCaptureValue(void)
{
    // Return the 16-bit Input Capture Register
    return ICR1;
}

void Timer1_SetCounter(u16 value) {
    TCNT1 = value;
}

void Timer1_Stop(void) {
    // Clear clock source bits in TCCR1B
    TCCR1B &= 0xF8;
}
