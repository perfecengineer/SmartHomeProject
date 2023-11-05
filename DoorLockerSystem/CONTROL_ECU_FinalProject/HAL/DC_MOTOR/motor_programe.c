/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: DC Motor Drive ********************
***************** Date:  24/8/2023 ******************************************
*/

#include "motor_interface.h"
#include "../../MCAL/GPIO/gpio.h"
#if ENABLE_PIN            !=              CONNECTING_VCC
#include "../../MCAL/TIMER/timer_interface.h"
#include "../../MCAL/TIMER/timer_configuration.h"
/*** Macro for configuration the selection timer  ***/
#define SELECTION_TIMER   Timer0
#define SIZE_OF_TIMER     8
#endif
/********************* The implementations for usage functions *********************************/
/*** The implementation of initial function for motor , to set some of command ***/
void MOTOR_init(void)
{
	/*** Set the pins direction ***/
	GPIO_setupPinDirection(FIRST_PORT_FOR_FIRST_PIN,FIRST_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(SECOND_PORT_FOR_SECOND_PIN,SECOND_PIN,PIN_OUTPUT);
#if ENABLE_PIN            !=              CONNECTING_VCC
	/*** Call the initial  function of timer,and set timer in pwm_mode, any selection timer ***/
	iniat_Timer();
#endif
}
#if ENABLE_PIN            !=              CONNECTING_VCC
/*** This prototype of function use to determine the speed from 0% to 100% ***/
void MOTOR_speed(uint8 speed)
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
	DUTY_cycleForTimers(SELECTION_TIMER,duty,0);
}
#endif
/*** The implementation of function use to determine the motor rotation direction and speed ***/
void MOTOR_directon(uint8 direction)
{

	/*** Set the direction for motor ***/
	switch(direction)
	{
	case ANTI_CW:
				GPIO_writePin(FIRST_PORT_FOR_FIRST_PIN,FIRST_PIN,LOGIC_LOW);
				GPIO_writePin(SECOND_PORT_FOR_SECOND_PIN,SECOND_PIN,LOGIC_HIGH);
	break;
	case CW:
				GPIO_writePin(FIRST_PORT_FOR_FIRST_PIN,FIRST_PIN,LOGIC_HIGH);
				GPIO_writePin(SECOND_PORT_FOR_SECOND_PIN,SECOND_PIN,LOGIC_LOW);
	break;
	}

}
/*** The implementation of function use to stop the rotation of motor ***/
void STOP_rotatonOfMotor(void)
{

	GPIO_writePin(FIRST_PORT_FOR_FIRST_PIN,FIRST_PIN,LOGIC_LOW);
	GPIO_writePin(SECOND_PORT_FOR_SECOND_PIN,SECOND_PIN,LOGIC_LOW);

}
