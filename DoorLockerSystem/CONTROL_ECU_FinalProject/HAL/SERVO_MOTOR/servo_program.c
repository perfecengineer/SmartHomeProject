/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: Servo Motor Drive ***************************
***************** Date:  24/8/2023 ******************************************
*/
#include "../../MCAL/TIMER/timer_interface.h"
#include "servo_interface.h"

#if SELECTION_TIMER 		==			Timer0
#define PRE_SCALRE               TIMER0_CLOCK_SELECT
#elif SELECTION_TIMER 		==			Timer1
#define PRE_SCALRE               TIMER1_CLOCK_SELECT
#elif SELECTION_TIMER 		==			Timer2
#define PRE_SCALRE               TIMER2_CLOCK_SELECT
#endif
#if 	PRE_SCALRE < CPU_OSILLATOR_IN_MEGA_HZ
#error "Please change the pre_scalre to be bigger than number of cpu osillator per mega Hz";
#endif
/************** Set the tick time ****/
#define TickTimeInMicrSecond  (PRE_SCALRE / CPU_OSILLATOR_IN_MEGA_HZ)
/**** The implementation of initial function ***********/
void SERVO_init(void)
{
	/*** Set the top value ***/
	TIMER_setTopValue(TOP_VALUE_BY_MICRO_SECOND,USE_ICU_REG_TO_STORE_TOP_VALUE);
	/*** Enable the timer ***/
	iniat_Timer();
}
/**** The implementation of function use to set the angle of servo_motor ***/
uint8 SERVO_setAngle(uint8 angle)
{
	uint8 Error_state = NOTOK;
	float32 TimeForRequireAngle = 0;
	uint16 DutyForRequireAngle = 0;
	if((angle >= 0 ) && (angle <= 180 ))
	{
		TimeForRequireAngle = (angle/180.0) + 1;
		DutyForRequireAngle = ((uint16)(TimeForRequireAngle * 1000) / TickTimeInMicrSecond);
		DUTY_cycleForTimers(SELECTION_TIMER,DutyForRequireAngle,0);

		Error_state = OK;
	}
	return Error_state;
}
