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
#define MOTOR_INDEX           (2)
#define NUMBER_OF_MOTORS            MOTOR_INDEX
/*** Macros for direction ***/
#define ANTI_CW          0
#define CW 		         1
#define MOTOR_1          (0)
#define MOTOR_2          (1)
#if NUMBER_OF_MOTORS       ==      MOTOR_INDEX
/*** Select the port for first pin for motor ***/
#define MOTRO_2_FIRST_PORT_FOR_FIRST_PIN   	    	PORTA_ID
/*** Select the first pin for motor ***/
#define MOTRO_2_FIRST_PIN 						  	PIN6
/*** Select the port for second pin for motor ***/
#define MOTRO_2_SECOND_PORT_FOR_SECOND_PIN      	PORTA_ID
/*** Select the second pin for motor ***/
#define MOTRO_2_SECOND_PIN 							PIN7
#endif
/*** Select the port for first pin for motor ***/
#define MOTRO_1_FIRST_PORT_FOR_FIRST_PIN   	    	PORTB_ID
/*** Select the first pin for motor ***/
#define MOTRO_1_FIRST_PIN 						  	PIN0
/*** Select the port for second pin for motor ***/
#define MOTRO_1_SECOND_PORT_FOR_SECOND_PIN      	PORTB_ID
/*** Select the second pin for motor ***/
#define MOTRO_1_SECOND_PIN 							PIN1


/*** For Enable pin ***/
#define ENABLE_PIN                          CONNECTING_PWM_PIN //CONNECTING_VCC
/********************* The prototypes for usage functions *********************************/
/*** The prototype of initial function for motor , to set some of command ***/
void MOTOR_init(void);
#if ENABLE_PIN            ==              CONNECTING_PWM_PIN
/*** This prototype of function use to determine the speed from 0% to 100% ***/
void MOTOR_speed(uint8 speed,uint8 sele_motor);
#endif
/*** This prototype of function use to determine the motor rotation direction ***/
void MOTOR_directon(uint8 direction,uint8 sele_motor);
/*** This prototype of function use to stop the rotation of motor ***/
void STOP_rotatonOfMotor(uint8 sele_motor);



#endif
