/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: DC Motor Drive ********************
***************** Date:  24/8/2023 ******************************************
*/

#include "motor_interface.h"
#include "../../MCAL/GPIO/gpio.h"
#if ENABLE_PIN            ==              CONNECTING_PWM_PIN
#include "../../MCAL/TIMER/timer_interface.h"
#include "../../MCAL/TIMER/timer_configuration.h"
/*** Macro for configuration the selection timer  ***/
#define SELECTION_TIMER_FOR_MOTOR1   Timer0
#define SIZE_OF_TIMER               (8)
#if NUMBER_OF_MOTORS       ==       MOTOR_INDEX
#define SELECTION_TIMER_FOR_MOTOR2   Timer2
#define SIZE_OF_TIMER                (8)
#endif
#endif
/********************* The implementations for usage functions *********************************/
/*** The implementation of initial function for motor , to set some of command ***/
void MOTOR_init(void)
{
	/*** Set the pins direction ***/
	GPIO_setupPinDirection(MOTRO_1_FIRST_PORT_FOR_FIRST_PIN,MOTRO_1_FIRST_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTRO_1_SECOND_PORT_FOR_SECOND_PIN,MOTRO_1_SECOND_PIN,PIN_OUTPUT);
#if NUMBER_OF_MOTORS       ==      MOTOR_INDEX
	/*** Set the pins direction ***/
	GPIO_setupPinDirection(MOTRO_2_FIRST_PORT_FOR_FIRST_PIN,MOTRO_2_FIRST_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTRO_2_SECOND_PORT_FOR_SECOND_PIN,MOTRO_2_SECOND_PIN,PIN_OUTPUT);
#endif
#if ENABLE_PIN            ==              CONNECTING_PWM_PIN
	/*** Call the initial  function of timer,and set timer in pwm_mode, any selection timer ***/
	iniat_Timer();
#endif
}
#if ENABLE_PIN            ==              CONNECTING_PWM_PIN
/*** This prototype of function use to determine the speed from 0% to 100% ***/
void MOTOR_speed(uint8 speed,uint8 sele_motor)
{
	/*** The speed input from 0% to 100%   ***/
#if SIZE_OF_TIMER         ==             8
	uint8 duty = (uint16)(speed * 255)/(100);
#elif SIZE_OF_TIMER         ==           16
	uint16 duty =(uint16) (speed * 65535)/(100);
#endif
/*
 * duty = (((uint16)(speed * 2^(SIZE_OF_TIMER) )/(100)) - 1);
 * duty = (casting)((0 to 100) * (capacity of timer register)/100)-1
 */
	/*** Set the speed of motor by using the duty cycle ***/
	if(MOTOR_1 == sele_motor)
		DUTY_cycleForTimers(SELECTION_TIMER_FOR_MOTOR1,duty,0);
#if NUMBER_OF_MOTORS       ==      MOTOR_INDEX
	else
	    DUTY_cycleForTimers(SELECTION_TIMER_FOR_MOTOR2,duty,0);
#endif
}
#endif
/*** The implementation of function use to determine the motor rotation direction and speed ***/
void MOTOR_directon(uint8 direction,uint8 sele_motor)
{

	/*** Set the direction for motor ***/
	if(MOTOR_1 == sele_motor)
	{
		switch(direction)
		{
		case ANTI_CW:
					GPIO_writePin(MOTRO_1_FIRST_PORT_FOR_FIRST_PIN,MOTRO_1_FIRST_PIN,LOGIC_LOW);
					GPIO_writePin(MOTRO_1_SECOND_PORT_FOR_SECOND_PIN,MOTRO_1_SECOND_PIN,LOGIC_HIGH);
		break;
		case CW:
					GPIO_writePin(MOTRO_1_FIRST_PORT_FOR_FIRST_PIN,MOTRO_1_FIRST_PIN,LOGIC_HIGH);
					GPIO_writePin(MOTRO_1_SECOND_PORT_FOR_SECOND_PIN,MOTRO_1_SECOND_PIN,LOGIC_LOW);
		break;
		}
	}
#if NUMBER_OF_MOTORS       ==       MOTOR_INDEX
	else
	{
		switch(direction)
		{
		case ANTI_CW:
					GPIO_writePin(MOTRO_2_FIRST_PORT_FOR_FIRST_PIN,MOTRO_2_FIRST_PIN,LOGIC_LOW);
					GPIO_writePin(MOTRO_2_SECOND_PORT_FOR_SECOND_PIN,MOTRO_2_SECOND_PIN,LOGIC_HIGH);
		break;
		case CW:
					GPIO_writePin(MOTRO_2_FIRST_PORT_FOR_FIRST_PIN,MOTRO_2_FIRST_PIN,LOGIC_HIGH);
					GPIO_writePin(MOTRO_2_SECOND_PORT_FOR_SECOND_PIN,MOTRO_2_SECOND_PIN,LOGIC_LOW);
		break;
		}
	}
#endif


}
/*** The implementation of function use to stop the rotation of motor ***/
void STOP_rotatonOfMotor(uint8 sele_motor)
{
	if(MOTOR_1 == sele_motor)
	{
		GPIO_writePin(MOTRO_1_FIRST_PORT_FOR_FIRST_PIN,MOTRO_1_FIRST_PIN,LOGIC_LOW);
		GPIO_writePin(MOTRO_1_SECOND_PORT_FOR_SECOND_PIN,MOTRO_1_SECOND_PIN,LOGIC_LOW);
	}
#if NUMBER_OF_MOTORS       ==       MOTOR_INDEX
	else
	{
		GPIO_writePin(MOTRO_2_FIRST_PORT_FOR_FIRST_PIN,MOTRO_2_FIRST_PIN,LOGIC_LOW);
		GPIO_writePin(MOTRO_2_SECOND_PORT_FOR_SECOND_PIN,MOTRO_2_SECOND_PIN,LOGIC_LOW);
	}
#endif


}
