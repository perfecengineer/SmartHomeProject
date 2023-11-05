/*
 * eeprom.h
 *
 *  Created on: Oct 3, 2023
 *      Author: ACS
 */

#ifndef MCAL_INTERNAL_EEPROM_EEPROM_H_
#define MCAL_INTERNAL_EEPROM_EEPROM_H_
#include "../../UTILS/STD_TYPES.h"
void EEPROM_write(uint16 uiAddress, uint8 ucData);
uint8 EEPROM_read(uint16 uiAddress);



#endif /* MCAL_INTERNAL_EEPROM_EEPROM_H_ */
