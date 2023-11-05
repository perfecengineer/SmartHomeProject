/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: LED Drive ********************
***************** Date:  26/8/2023 ******************************************
*/
#ifndef LED_PRIVTE_H_
#define LED_PRIVTE_H_
#include "led_interface.h"

#if PIN_TO_LED      ==      ENABLE
/*** This function use to on the led ***/
static void LED_onFunction(uint8 selectPort,uint8 selectPin);
/*** This function use to off the led ***/
static void LED_offFunction(uint8 selectPort,uint8 selectPin);
/*** This function use to toggle the led ***/
static void LED_toggleFunction(uint8 selectPort,uint8 selectPin);
#endif
#if PORT_OF_LED     ==      ENABLE
/*** This function use to on the port of leds ***/
static void PORT_onFunction(uint8 selectPort);
/*** This function use to off the port of leds ***/
static void PORT_offFunction(uint8 selectPort);
/*** This function use to toggle the port of leds ***/
static void PORT_toggleFunction(uint8 selectPort);
#endif /* HAL_LED_LED_PRVITE_H_ */
#endif
