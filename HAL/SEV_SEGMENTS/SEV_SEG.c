#include "SEV_SEG.h"

static const u8 seg[SEG_SIZE] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void Seg_Init(DIO_PORT_TYPE port)
{
	
	switch(port)
	{
		case PA: DDRA = 0x7F; break;
		case PB: DDRB = 0x7F; break;
		case PC: DDRC = 0x7F; break;
		case PD: DDRD = 0x7F; break;
	}
}

void Seg_Display_num(DIO_PORT_TYPE port, u8 num)
{ 
	if(num < SEG_SIZE)
	{
		switch(port)
		{
			case PA: PORTA = seg[num]; break;
			case PB: PORTB = seg[num]; break;
			case PC: PORTC = seg[num]; break;
			case PD: PORTD = seg[num]; break;
		}
	}
}

void Seg_Display_All(DIO_PORT_TYPE port)
{
	for(int i = 0; i < SEG_SIZE; i++)
	{
		Seg_Display_num(port, i);
		_delay_ms(500);
	}
}