/*
 * app_sw_components.h
 *
 *  Created on: Oct 22, 2023
 *      Author: ACS
 */

#ifndef APP_APP_SW_COMPONENTS_H_
#define APP_APP_SW_COMPONENTS_H_

#include "../UTILS/STD_TYPES.h"

#define OPEN_DOOR       (270)
#define CLOSE_DOOR      (0)
#define MAX_DISTANCE    (100)

void SW_initFunctions(void);
void DOOR_openAndClose(void);
void ResetFunction(void);
void LCD_staticSentences(void);
void LCD_sleepMode(void);
#endif /* APP_APP_SW_COMPONENTS_H_ */
