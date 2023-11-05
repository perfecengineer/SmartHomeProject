#ifndef INTERRUPT_CONFIGURATION_H
#define INTERRUPT_CONFIGURATION_H

#include "../GPIO/gpio_configuration.h"

/****************** Port configruration for interrupt sources ****************/
#define EXT0_PORT_ID            PORTD_ID    
#define EXT1_PORT_ID            PORTD_ID 
#define EXT2_PORT_ID            PORTB_ID

/******************External pins for interrupt sources ****************/
#define EXT0_PIN            PIN2    
#define EXT1_PIN            PIN3 
#define EXT2_PIN            PIN2 

/******************************** External interrupt sources **************/
#define EXTINT0            0
#define EXTINT1            1
#define EXTINT2            2
/*************************Source triggering for interrupt:******************/

#define FALLING_EDGE         0
#define RISING_EDGE          1
#define LOW_LEVEL_EDGE       2
#define ANY_LOGIC_CHANGE     3
/*******************Control register for interrupt sources:**********************/

/****************** Bits numbers in control regester for detection edge for EXT0 */
#define EXT0_BIT0				0 
#define EXT0_BIT1				1
/*******************Bits numbers in control regester for detection edge for EXT1 */
#define EXT1_BIT0				2 
#define EXT1_BIT1				3
/*******************Bit number in control regester for detection edge for EXT2 */
#define EXT2_BIT6				6
/********************** Enable register for interrupt sources:*/

/******** Bit number in control regester to enable the external interrupt (EXT0) */
#define ENABLE_EXT0_BIT			6
/*********Bit number in control regester to enable the external interrupt (EXT1) */
#define ENABLE_EXT1_BIT			7
/*********Bit number in control regester to enable the external interrupt (EXT2) */
#define ENABLE_EXT2_BIT			5

/****************************Maskable register for interrupt sources:**************/

/*************************** Bit number in flag regester for EXT0 */
#define FLAG_EXT0_BIT			6
/*************************** Bit number in flag regester for EXT1 */
#define FLAG_EXT1_BIT	        7
/**************************  Bit number in flag regester for EXT2 */
#define FLAG_EXT2_BIT           5


/************************** This macros for readability: ********************/
#define ENABLE                  1	
#define DISABLE                 0

#endif
