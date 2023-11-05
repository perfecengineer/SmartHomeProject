#ifndef TIMER_REGISTER_H
#define TIMER_REGISTER_H
/***************** Content of standard library ************/
#include "../../UTILS/STD_TYPES.h"
#include "timer_interface.h"
/****** Timer0 mapped registers **************************/
#define CONTROL_REG_TIMER0                *((volatile uint8 *)0x53)
#define DATA_REG_TIMER0                   *((volatile uint8 *)0x52)
#define OUTPUT_COMPARE_REG_TIMER0         *((volatile uint8 *)0x5C)

/****** Timer1 mapped registers ****************************/
#define CONTROL_REG_TIMER1A                *((volatile uint8 *)0x4F)
#define CONTROL_REG_TIMER1B                *((volatile uint8 *)0x4E)
#define DATA_REG_TIMER1                    *((volatile uint16 *)0x4C)
#define OUTPUT_COMPARE_REG_TIMER1A         *((volatile uint16 *)0x4A)
#define OUTPUT_COMPARE_REG_TIMER1B         *((volatile uint16 *)0x48)
#define INPUT_CAPTURE_REGISTER_TIMER1      *((volatile uint16 *)0x46)
/****** Timer2 mapped registers **********************************/
#define CONTROL_REG_TIMER2                *((volatile uint8 *)0x45)
#define DATA_REG_TIMER2                   *((volatile uint8 *)0x44)
#define OUTPUT_COMPARE_REG_TIMER2         *((volatile uint8 *)0x43)


/****** Mask register to enable the interrupt for timers ********/
#define MASKABLE_REG_TIMERS         *((volatile uint8 *)0x59)

/****** Flags register for interrupt timers ***********************/
#define FLAGS_REG_TIMERS            *((volatile uint8 *)0x58)








#endif
