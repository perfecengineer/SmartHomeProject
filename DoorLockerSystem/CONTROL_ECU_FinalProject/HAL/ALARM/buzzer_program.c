/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: LED Drive ********************
***************** Date:  26/8/2023 ******************************************
*/
#include "buzzer_interface.h"
#include "../../MCAL/GPIO/gpio.h"
#include "buzzer_privte.h"


/*** This is implementation of function use to set the the pin direction to output pin ***/
uint8 BUZZER_initForPin(uint8 selectPort,uint8 selectPin)
{
	uint8 ErrorState = NOTOK;
	if(((selectPort >= PORTA_ID) && (selectPort <= PORTD_ID)) && ((selectPin >= PIN0) && (selectPin <= PIN7)))
	{
		/********** Set the pin direction *******/
		GPIO_setupPinDirection(selectPort,selectPin,PIN_OUTPUT);
		/**** Close the buzzer in the start  *********/
		BUZZER_offFunction(selectPort,selectPin);
		ErrorState = OK;
	}
	return ErrorState;
}
/*** The implementation of function use to set the state for buzzer ***/
uint8 BUZZER_enable(uint8 selectPort,uint8 selectPin,uint8 buzzer_State)
{
	uint8 ErrorState = NOTOK;
	if(((selectPort >= PORTA_ID) && (selectPort <= PORTD_ID)) && ((selectPin >= PIN0) && (selectPin <= PIN7)))
	{
		switch(buzzer_State)
		{
		case BUZZER_OFF:BUZZER_offFunction(selectPort,selectPin);break;
		case BUZZER_ON:BUZZER_onFunction(selectPort,selectPin);break;
		case BUZZER_TOGGLE:BUZZER_toggleFunction(selectPort,selectPin);break;
		ErrorState = OK;
		}
	}
	return ErrorState;
}
/*** This function use to on the Alarm ***/
static void BUZZER_onFunction(uint8 selectPort,uint8 selectPin)
{
#if	LOGIC_OF_BUZZER    ==    POSITIVE_LOGIC
	GPIO_writePin(selectPort,selectPin,LOGIC_HIGH);
#elif LOGIC_OF_BUZZER    ==    NEGATIVE_LOGIC
	GPIO_writePin(selectPort,selectPin,LOGIC_LOW);
#endif
}
/*** This function use to off the Alarm ***/
static void BUZZER_offFunction(uint8 selectPort,uint8 selectPin)
{
#if	LOGIC_OF_BUZZER    ==    POSITIVE_LOGIC
	GPIO_writePin(selectPort,selectPin,LOGIC_LOW);
#elif LOGIC_OF_BUZZER    ==    NEGATIVE_LOGIC
	GPIO_writePin(selectPort,selectPin,LOGIC_HIGH);
#endif
}
/*** This function use to toggle the Alarm ***/
static void BUZZER_toggleFunction(uint8 selectPort,uint8 selectPin)
{
	static uint8 flag = 1;
	if(flag)
	{
		GPIO_writePin(selectPort,selectPin,LOGIC_HIGH);
		flag = 0;
	}
	else
	{
		GPIO_writePin(selectPort,selectPin,LOGIC_LOW);
		flag = 1;
	}
}
