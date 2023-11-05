/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: TWI Drive ***********************************
***************** Date:  25/9/2023 ******************************************
*/
#ifndef MCAL_TWI_TWI_REGISTERS_H_
#define MCAL_TWI_TWI_REGISTERS_H_
#include "../../UTILS/STD_TYPES.h"
/*******************TWI  Redefine Registers ****/
/**** Two-wire Serial Interface Bit Rate Register ***/
#define TWI_BIT_RATE_REG       (*((volatile uint8 *)(0x20)))
/**** Two-wire Serial Interface Status Register ***/
#define TWI_STATUS_REG         (*((volatile uint8 *)(0x21)))
/**** Two-wire Serial Interface Address Register ***/
#define TWI_SLAVE_ADDRESS_REG  (*((volatile uint8 *)(0x22)))
/**** Two-wire Serial Interface Data Register ***/
#define TWI_DATA_REG           (*((volatile uint8 *)(0x23)))
/**** Two-wire Serial Interface Control Register ***/
#define TWI_CONTROL_REG        (*((volatile uint8 *)(0x56)))




#endif /* MCAL_TWI_TWI_REGISTERS_H_ */
