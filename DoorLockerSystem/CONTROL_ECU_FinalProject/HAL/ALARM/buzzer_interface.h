/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: LED Drive ********************
***************** Date:  26/8/2023 ******************************************
*/

#ifndef BUZZER_INTERFACE_H_
#define BUZZER_INTERFACE_H_
#include "../../MCAL/GPIO/gpio_configuration.h"
#include "../../UTILS/STD_TYPES.h"
/*** Buzzer states ***/
#define BUZZER_OFF        0
#define BUZZER_ON         1
#define BUZZER_TOGGLE     2
/*** Alarm logic ***/
#define LOGIC_OF_BUZZER       POSITIVE_LOGIC
/*** This is prototype of function use to set the the pin direction to output pin ***/
uint8 BUZZER_initForPin(uint8 selectPort,uint8 selectPin);
/*** The prototype of function use to set the state for buzzer ***/
uint8 BUZZER_enable(uint8 selectPort,uint8 selectPin,uint8 buzzer_State);
#endif

