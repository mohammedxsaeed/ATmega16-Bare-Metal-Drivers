/*
 * EXT_Interrupt.c
 *
 * Created: 8/12/2025
 * Author: Mohammed Saeed
 */ 
#include "EXT_Interrupt.h"

void INTERRUPT_Init(u8 pin, u8 mode)
{

    switch(pin)
    { 
        case INT0_PIN: 
            CLR_BIT(DDRD, 2);
            SET_BIT(PORTD, 2); // Enable Pull-up
            
            // Clear Bits 0, 1 (ISC00, ISC01) then set the mode
            MCUCR &= ~(0x03); 
            MCUCR |= (mode & 0x03);
            
            SET_BIT(GICR, 6); // Enable INT0
            break;
        
        case INT1_PIN: 
            CLR_BIT(DDRD, 3);
            SET_BIT(PORTD, 3); // Enable Pull-up
            
            // Clear Bits 2, 3 (ISC10, ISC11) then set the mode shifted by 2
            MCUCR &= ~(0x0C); 
            MCUCR |= ((mode & 0x03) << 2);
            
            SET_BIT(GICR, 7); // Enable INT1 (Bit 7)
            break;
            
        case INT2_PIN: 
           if(mode != Falling_edge && mode != Rising_edge)
           break;
		    CLR_BIT(DDRB, 2);
            SET_BIT(PORTB, 2); // Enable Pull-up
            
            // INT2 uses ISC2 (6) in MCUCSR for edge selection
            if(mode == Falling_edge)
                CLR_BIT(MCUCSR, 6);
            else if(mode == Rising_edge)
                SET_BIT(MCUCSR, 6);
                
            SET_BIT(GICR, 5); // Enable INT2 
            break;
    }
}