/*
 * Timer.h
 *
 * Created: 8/16/2025 4:02:05 PM
 *  Author: Mohammed Saeed
 */


#ifndef TIMER_H_
#define TIMER_H_
#include "STD_TYPES.h"
#include "UTILS.h"
#include "MemMAP.h"
#include <avr/interrupt.h>
/*******************************************/

// Prescaler Options for Timer0
#define TIMER0_STOPPED      0
#define TIMER0_PRESCALER_1  (1 << 0) // (1 << CS00)
#define TIMER0_PRESCALER_8  (1 << 1) // (1 << CS01)
#define TIMER0_PRESCALER_64 ((1 << 1) | (1 << 0))   // (1 << CS01) | (1 << CS00))
#define TIMER0_PRESCALER_256 (1 << 2)               // (1 << CS02)
#define TIMER0_PRESCALER_1024 ((1 << 2) | (1 << 0)) //((1 << CS02) | (1 << CS00))

// Prescaler Options for Timer1
#define TIMER1_STOPPED      0
#define TIMER1_PRESCALER_1  (1 << 0) // (1 << CS10)
#define TIMER1_PRESCALER_8  (1 << 1) // (1 << CS11)
#define TIMER1_PRESCALER_64 ((1 << 1) | (1 << 0))   // (1 << CS11) | (1 << CS10))
#define TIMER1_PRESCALER_256 (1 << 2)               // (1 << CS12)
#define TIMER1_PRESCALER_1024 ((1 << 2) | (1 << 0)) //((1 << CS12) | (1 << CS10))
typedef enum {
    TIMER_NORMAL_MODE = 0,
    TIMER_PWM_PHASE_CORRECT = 1,
    TIMER_CTC_MODE = 2,
    TIMER_FAST_PWM = 3
} Timer_Mode_t;

/// Timer1 Input Capture Edge
typedef enum {
    FALLING_EDGE = 0,
    RISING_EDGE = 1
} ICU_Edge_t;

/******************* Function Prototypes *******************/

void Timer0_Init(Timer_Mode_t mode, u8 prescaler);
void Timer0_SetCompareValue(u8 value);
void Timer0_SetCounter(u8 value);
void Timer0_Stop(void);

void Timer1_Init_Normal(u8 prescaler);
void Timer1_ICU_Init(ICU_Edge_t edge);
void Timer1_ICU_SetEdge(ICU_Edge_t edge);
u16  Timer1_ICU_GetCaptureValue(void);
void Timer1_SetCounter(u16 value);
void Timer1_Stop(void);


#endif /* TIMER_H_ */
