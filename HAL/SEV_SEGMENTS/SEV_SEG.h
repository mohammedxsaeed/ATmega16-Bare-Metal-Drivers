
#ifndef SEV_SEG_H_
#define SEV_SEG_H_

#define F_CPU	8000000UL
#include "STD_TYPES.h"
#include "UTILS.h"
#include "MemMAP.h"
#include "DIO/DIO.h"
#include <util/delay.h>

#define SEG_SIZE  10

void Seg_Init(DIO_PORT_TYPE port);
void Seg_Display_num(DIO_PORT_TYPE port, u8 num);
void Seg_Display_All(DIO_PORT_TYPE port);

#endif /* SEV_SEG_H_ */
