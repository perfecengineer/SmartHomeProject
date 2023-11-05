/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: LED Drive ********************
***************** Date:  26/8/2023 ******************************************
*/
#include "led_interface.h"
#include "../../MCAL/GPIO/gpio.h"
#include "led_privte.h"

/***************** For port of leds ************************/
#if PORT_OF_LED     ==      ENABLE
/*** This is implementation of function use to set the the port direction to output port ***/
uint8 LEDS_initForPort(uint8 selectPort)
{
	uint8 ErrorState = NOTOK;
	if((selectPort >= PORTA_ID) && (selectPort <= PORTD_ID))
	{
		/****** Set the direction of port ***/
		GPIO_setupPortDirection(selectPort,PORT_OUTPUT);
		/****** Close the leds in the first    ***/
		PORT_offFunction(selectPort);
		ErrorState = OK;
	}
	return ErrorState;
}
/*** The implementation of function use to set the state for leds ***/
uint8 LEDS_enableForPort(uint8 selectPort,uint8 PortState)
{
	uint8 ErrorState = NOTOK;
	if((selectPort >= PORTA_ID) && (selectPort <= PORTD_ID))
	{
		switch(PortState)
		{
		case PORT_OFF:PORT_offFunction(selectPort);break;
		case PORT_ON:PORT_onFunction(selectPort);break;
		case PORT_TOGGLE:PORT_toggleFunction(selectPort);break;
		ErrorState = OK;
		}
	}
	return ErrorState;
}
/*** This function use to on the port of leds ***/
static void PORT_onFunction(uint8 selectPort)
{
#if	LOGIC_OF_PORT    ==    POSITIVE_LOGIC
	GPIO_writePort(selectPort,0xFF);
#elif LOGIC_OF_PORT        NEGATIVE_LOGIC
	GPIO_writePort(selectPort,0x00);
#endif
}
/*** This function use to off the port of leds ***/
static void PORT_offFunction(uint8 selectPort)
{
#if	LOGIC_OF_PORT    ==    POSITIVE_LOGIC
	GPIO_writePort(selectPort,0x00);
#elif LOGIC_OF_PORT        NEGATIVE_LOGIC
	GPIO_writePort(selectPort,0xFF);
#endif
}
/*** This function use to toggle the port of leds ***/
static void PORT_toggleFunction(uint8 selectPort)
{
	static uint8 flag = 1;
	if(flag)
	{
		GPIO_writePort(selectPort,0xFF);
		flag = 0;
	}
	else
	{
		GPIO_writePort(selectPort,0x00);
		flag = 1;
	}
}

#endif
/***************** For each led ************************/
#if PIN_TO_LED      ==      ENABLE
/*** This is implementation of function use to set the the pin direction to output pin ***/
uint8 LED_initForPin(uint8 selectPort,uint8 selectPin)
{
	uint8 ErrorState = NOTOK;
	if(((selectPort >= PORTA_ID) && (selectPort <= PORTD_ID)) && ((selectPin >= PIN0) && (selectPin <= PIN7)))
	{
		/********** Set the pin direction *******/
		GPIO_setupPinDirection(selectPort,selectPin,PIN_OUTPUT);
		/**** Close the led in the first  *********/
		LED_offFunction(selectPort,selectPin);
		ErrorState = OK;
	}
	return ErrorState;
}
/*** The implementation of function use to set the state for led ***/
uint8 LED_enable(uint8 selectPort,uint8 selectPin,uint8 ledState)
{
	uint8 ErrorState = NOTOK;
	if(((selectPort >= PORTA_ID) && (selectPort <= PORTD_ID)) && ((selectPin >= PIN0) && (selectPin <= PIN7)))
	{
		switch(ledState)
		{
		case LED_OFF:LED_offFunction(selectPort,selectPin);break;
		case LED_ON:LED_onFunction(selectPort,selectPin);break;
		case LED_TOGGLE:LED_toggleFunction(selectPort,selectPin);break;
		ErrorState = OK;
		}
	}
	return ErrorState;
}
/*** This function use to on the led ***/
static void LED_onFunction(uint8 selectPort,uint8 selectPin)
{
#if	LOGIC_OF_LED    ==    POSITIVE_LOGIC
	GPIO_writePin(selectPort,selectPin,LOGIC_HIGH);
#elif LOGIC_OF_LED    ==    NEGATIVE_LOGIC
	GPIO_writePin(selectPort,selectPin,LOGIC_LOW);
#endif
}
/*** This function use to off the led ***/
static void LED_offFunction(uint8 selectPort,uint8 selectPin)
{
#if	LOGIC_OF_LED    ==    POSITIVE_LOGIC
	GPIO_writePin(selectPort,selectPin,LOGIC_LOW);
#elif LOGIC_OF_LED    ==    NEGATIVE_LOGIC
	GPIO_writePin(selectPort,selectPin,LOGIC_HIGH);
#endif
}
/*** This function use to toggle the led ***/
static void LED_toggleFunction(uint8 selectPort,uint8 selectPin)
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

#endif
