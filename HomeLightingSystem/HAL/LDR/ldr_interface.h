/*
 * ldr_interface.h
 *
 *  Created on: Oct 27, 2023
 *      Author: ACS
 */

#ifndef HAL_LDR_LDR_INTERFACE_H_
#define HAL_LDR_LDR_INTERFACE_H_
#include "../../UTILS/STD_TYPES.h"

/*** ProtoType of function use to read the value of channel that connected by LDR sensor ***/
#define THE_MAX_DUTY_OF_LED              256.0
#define THE_MAX_RESOLUTION_OF_ADC       1023.0
uint8 LDR_readChannel(uint8 Channel);
#endif /* HAL_LDR_LDR_INTERFACE_H_ */
