/*
 * app_sw_components.h
 *
 *  Created on: Oct 22, 2023
 *      Author: ACS
 */

#ifndef APP_APP_SW_COMPONENTS_H_
#define APP_APP_SW_COMPONENTS_H_

#include "../UTILS/STD_TYPES.h"
extern volatile uint8 g_DutyCycleOfRoom;
extern volatile uint8 g_DutyCycleOfReception;
#endif /* APP_APP_SW_COMPONENTS_H_ */
void APP_initOfAllUsagePeripheral(void);
void LDR_controlDutyCycl(uint8 RoomFlag,uint8 Reception);
