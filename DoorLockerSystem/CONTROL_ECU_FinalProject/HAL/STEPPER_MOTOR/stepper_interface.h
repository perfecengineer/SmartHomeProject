/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: Stepper Motor Drive ********************
***************** Date:  26/8/2023 ******************************************
*/
#ifndef STEPPER_INTERFACE_H_
#define STEPPER_INTERFACE_H_
#include "../../UTILS/STD_TYPES.h"
#include "../../MCAL/GPIO/gpio_configuration.h"
/*********************** Sequence types ********************/
#define FULL_STEP_SEQUENCE           4
#define HALF_STEP_SEQUENCE           8
/*** Select the type of stepper motor ***/
#define STEPPER_MOTOR_SELECTED              UNIPOLAR// OR BIPOLAR
#if STEPPER_MOTOR_SELECTED     		==      UNIPOLAR
/*** Define the number of wires ***/
#define NUMBER_OF_WIRES                     4
/*** The port for pins ***/
#define STEPPER_SELECTION_PORT_FOR_PINS    		   PORTB_ID
/*** The first pin ***/
#define STEPPER_FIRST_PIN					PIN0
/*** The second pin ***/
#define STEPPER_SECOND_PIN					PIN1
/*** The third pin ***/
#define STEPPER_THIRD_PIN					PIN2
/*** The fourth pin ***/
#define STEPPER_FOURTH_PIN					PIN3

#elif STEPPER_MOTOR_SELECTED   		==	    BIPOLAR
/***********************************
 *
 *
 * */
#endif
/***************** Select the sequence ***********/
#define TYPE_OF_SEQUANCE 				 HALF_STEP_SEQUENCE
/*** The prototype of initial function  of stepper motor ***/
void STEPPER_init(void);
/*** The prototype of function use to determine the angle ***/
uint8 STEPPER_angle(uint16 angle);
#endif /* HAL_STEPPER_MOTOR_STEPPER_INTERFACE_H_ */
