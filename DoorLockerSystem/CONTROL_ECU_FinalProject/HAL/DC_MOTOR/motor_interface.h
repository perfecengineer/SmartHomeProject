/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: DC Motor Drive ********************
***************** Date:  24/8/2023 ******************************************
*/
#ifndef MOTOR_INTERFACE_H
#define MOTOR_INTERFACE_H
#include "../../MCAL/GPIO/gpio_configuration.h"
#include "../../UTILS/STD_TYPES.h"
/*** Macros for direction ***/
#define ANTI_CW          0
#define CW 		         1
/*** Select the port for first pin for motor ***/
#define FIRST_PORT_FOR_FIRST_PIN   	    	PORTD_ID
/*** Select the first pin for motor ***/
#define FIRST_PIN 						  	PIN6
/*** Select the port for second pin for motor ***/
#define SECOND_PORT_FOR_SECOND_PIN      	PORTD_ID
/*** Select the second pin for motor ***/
#define SECOND_PIN 							PIN7
/*** For Enable pin ***/
#define ENABLE_PIN                          CONNECTING_VCC//CONNECTING_PWM_PIN
/********************* The prototypes for usage functions *********************************/
/*** The prototype of initial function for motor , to set some of command ***/
void MOTOR_init(void);
#if ENABLE_PIN            !=              CONNECTING_VCC
/*** This prototype of function use to determine the speed from 0% to 100% ***/
void MOTOR_speed(uint8 speed);
#endif
/*** This prototype of function use to determine the motor rotation direction ***/
void MOTOR_directon(uint8 direction);
/*** This prototype of function use to stop the rotation of motor ***/
void STOP_rotatonOfMotor(void);



#endif
