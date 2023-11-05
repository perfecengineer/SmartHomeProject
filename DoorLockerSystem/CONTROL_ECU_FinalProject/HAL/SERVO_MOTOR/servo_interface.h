/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: Servo Motor Drive ***************************
***************** Date:  24/8/2023 ******************************************
*/
#ifndef SERVO_INTERFACE_H_
#define SERVO_INTERFACE_H_
#include "../../UTILS/STD_TYPES.h"
#include "../../MCAL/TIMER/timer_configuration.h"
#define TOP_VALUE_BY_MICRO_SECOND          	2499
#define SELECTION_TIMER 					Timer1
#define CPU_OSILLATOR_IN_MEGA_HZ            8



/**** The prototype of initial function ***********/
void SERVO_init(void);
/**** The prototype of function use to set the angle of servo_motor ***/
uint8 SERVO_setAngle(uint8 angle);




#endif /* HAL_SEROV_MOTOR_SERVO_INTERFACE_H_ */
