/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: Stepper Motor Drive ********************
***************** Date:  26/8/2023 ******************************************
*/
#include "stepper_interface.h"
#include "../../MCAL/GPIO/gpio.h"

#if TYPE_OF_SEQUANCE 		==		 FULL_STEP_SEQUENCE
/***** Store the angles 90 -> 180 -> 270 -> 360 or 0 in this array ***/
static uint8 ArrayOfSteppingAngles[FULL_STEP_SEQUENCE] = {0x0C,0x06,0x03,0x09};
#define STEPPER_ANGLE          90
#elif TYPE_OF_SEQUANCE 		==		 HALF_STEP_SEQUENCE
/***** Store the angles 45 -> 90 -> 135 -> 180 -> 225 -> 270 -> 315 -> 360 or 0 in this array ***/
static uint8 ArrayOfSteppingAngles[HALF_STEP_SEQUENCE] = {0x0C,0x04,0x06,0x02,0x03,0x01,0x09,0x0};
#define STEPPER_ANGLE          45
#endif
/*** The implementation of initial function  of stepper motor ***/
void STEPPER_init(void)
{
#if STEPPER_MOTOR_SELECTED     		==      UNIPOLAR
	/*** Set the direction for the first pin ***/
	GPIO_setupPinDirection(STEPPER_SELECTION_PORT_FOR_PINS,STEPPER_FIRST_PIN,PIN_OUTPUT);
	/*** Set the direction for the second pin ***/
	GPIO_setupPinDirection(STEPPER_SELECTION_PORT_FOR_PINS,STEPPER_SECOND_PIN,PIN_OUTPUT);
	/*** Set the direction for the third pin ***/
	GPIO_setupPinDirection(STEPPER_SELECTION_PORT_FOR_PINS,STEPPER_THIRD_PIN,PIN_OUTPUT);
	/*** Set the direction for the fourth pin ***/
	GPIO_setupPinDirection(STEPPER_SELECTION_PORT_FOR_PINS,STEPPER_FOURTH_PIN,PIN_OUTPUT);
#elif STEPPER_MOTOR_SELECTED   		==	    BIPOLAR
/***********************************
 *
 *
 * */
#endif
}
/*** The implementation of function use to determine the angle ***/
uint8 STEPPER_angle(uint16 angle)
{
	uint8 ErrorState = NOTOK;
	uint8 NumberOfStepping = (angle / STEPPER_ANGLE);
	if(angle >= STEPPER_ANGLE && angle <= 360)
	{
	//	_delay_ms(10);
		GPIO_writePort(STEPPER_SELECTION_PORT_FOR_PINS,ArrayOfSteppingAngles[NumberOfStepping - 1]);// the other pin clear?in this port
		ErrorState = OK;
	}
	return ErrorState;

}
