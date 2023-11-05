/*
 * app_sw_components.h
 *
 *  Created on: Oct 22, 2023
 *      Author: ACS
 */

#ifndef APP_APP_SW_COMPONENTS_H_
#define APP_APP_SW_COMPONENTS_H_

#include "../UTILS/STD_TYPES.h"
#define TURN_ON_THE_SYSTEM       (1)
#define TURN_OFF_THE_SYSTEM      (0)
#define UART_BAUD_RATE           (9600)

void CLOSE_systemFunction(void);
void OPEN_systemFunction(void);
void LCD_staticSentences(void);
void LCD_sleepMode(void);
#endif /* APP_APP_SW_COMPONENTS_H_ */
