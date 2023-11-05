/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: LED Drive ********************
***************** Date:  26/8/2023 ******************************************
*/

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_
#include "../../MCAL/GPIO/gpio_configuration.h"
#include "../../UTILS/STD_TYPES.h"
/********** For each pin *******/
#define PIN_TO_LED            ENABLE
/********** For each port *******/
#define PORT_OF_LED           DISABLE
/********** For port of leds ****/
#if PORT_OF_LED     ==      ENABLE
/**** Led logic    ***/
#define LOGIC_OF_PORT        POSITIVE_LOGIC // or NEGATIVE_LOGIC
/*** Port states ***/
#define PORT_OFF        0
#define PORT_ON         1
#define PORT_TOGGLE     2
/*** This is prototype of function use to set the the port direction to output port ***/
uint8 LEDS_initForPort(uint8 selectPort);
/*** The prototype of function use to set the state for leds ***/
uint8 LEDS_enableForPort(uint8 selectPort,uint8 PortState);
#endif
#if PIN_TO_LED      ==      ENABLE
/**** Led logic    ***/
#define LOGIC_OF_LED        POSITIVE_LOGIC // or NEGATIVE_LOGIC
/*** Led states ***/
#define LED_OFF        0
#define LED_ON         1
#define LED_TOGGLE     2
/*** This is prototype of function use to set the the pin direction to output pin ***/
uint8 LED_initForPin(uint8 selectPort,uint8 selectPin);
/*** The prototype of function use to set the state for led ***/
uint8 LED_enable(uint8 selectPort,uint8 selectPin,uint8 ledState);
#endif
#endif
