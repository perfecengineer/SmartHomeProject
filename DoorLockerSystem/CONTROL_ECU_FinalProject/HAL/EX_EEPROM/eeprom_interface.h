/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: EEPROM Drive ***********************************
***************** Date:  25/9/2023 ******************************************
*/
#ifndef HAL_EX_EEPROM_EEPROM_INTERFACE_H_
#define HAL_EX_EEPROM_EEPROM_INTERFACE_H_
#include "../../MCAL/TWI/twi_interface.h"
#define ERROR          0
#define SUCCESS        1

/**** Function Prototype used for write byte of EEPROM ***/
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
/**** Function Prototype used for read byte of EEPROM ***/
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);
/**** Function Prototype used for write string of EEPROM ***/
uint8 EEPROM_writeString(uint16 u16StratAddress,uint8* string);
/**** Function Prototype used for read string of EEPROM ***/
uint8 EEPROM_readString(uint16 u16StratAddress,uint8* string);
#endif /* HAL_EX_EEPROM_EEPROM_INTERFACE_H_ */
