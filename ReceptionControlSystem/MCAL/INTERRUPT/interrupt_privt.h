#ifndef INTERRUPT_PRIVT_H
#define INTERRUPT_PRIVT_H
#include "../../UTILS/STD_TYPES.h"
/*
	Redefine the name of each register in peripheral by using the its phyiscal address.
*/

/*	Control register for external interrupt zero.	*/
#define INTERRUPT_CONTER_REGISTER_EXT0				      *((volatile uint8 *)0X55)
/*	Control register for external interrupt one.	*/
#define INTERRUPT_CONTER_REGISTER_EXT1					  INTERRUPT_CONTER_REGISTER_EXT0
/*	Control register for external interrupt two.	*/
#define INTERRUPT_CONTER_REGISTER_EXT2				      *((volatile uint8 *)0X54)
/*	Enable register for each external interrupt.	*/
#define INTERRUPT_ENABLE_REGISTER_EXT0			          *((volatile uint8 *)0X5B)
#define INTERRUPT_ENABLE_REGISTER_EXT1					  *((volatile uint8 *)0X5B)
#define INTERRUPT_ENABLE_REGISTER_EXT2					  *((volatile uint8 *)0X5B)
/*	Maskable register for external interrupts.	*/
#define INTERRUPT_MASK_REGISTER_EXT0_EXT1_EXT2			  *((volatile uint8 *)0X5A)
/* Array of pointer to functions of three elements for each interrupt source:*/
static void (* ArrPtrToFunction[ARRAY_ELEMENTS])(void) = {NULL_PTR,NULL_PTR,NULL_PTR};



#endif
