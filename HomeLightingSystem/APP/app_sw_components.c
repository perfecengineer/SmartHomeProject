/*
 * app_sw_components.c
 *
 *  Created on: Oct 22, 2023
 *      Author: ACS
 */
#include "util/delay.h"
#include "app_sw_components.h"
#include "../MCAL/GPIO/gpio.h"
#include "../HAL/LDR/ldr_interface.h"
#include "../MCAL/ADC/adc_interface.h"
#include "../HAL/LCD/lcd.h"
#include "../MCAL/TIMER/timer_interface.h"
volatile uint8 g_DutyCycleOfRoom = 0;
volatile uint8 g_DutyCycleOfReception = 0;
void APP_initOfAllUsagePeripheral(void)
{
	LCD_init();
	ADC_init();
	iniat_Timer();
}
void LDR_controlDutyCycl(uint8 RoomFlag,uint8 ReceptionFalg)
{
	uint16 ValueOfLDR = 0;
	/*** For timer 0 ***/
	if(RoomFlag == 0)
	{
		/***************************/
		ValueOfLDR = LDR_readChannel(CH0);
		/********************/
		g_DutyCycleOfRoom = ((float)(ValueOfLDR / THE_MAX_DUTY_OF_LED) * 100 );
	}
	/*******************************************/
	if(g_DutyCycleOfRoom <= 25 && g_DutyCycleOfRoom >= 20)
	{
		LCD_displayStringRowColumn(3,10,"25 ");
		DUTY_cycleForTimers(Timer0,ValueOfLDR,0);
	}
	else if(g_DutyCycleOfRoom <= 50)
	{
		LCD_displayStringRowColumn(3,10,"50 ");
		DUTY_cycleForTimers(Timer0,ValueOfLDR,0);
	}
	else if(g_DutyCycleOfRoom <= 75)
	{
		LCD_displayStringRowColumn(3,10,"75 ");
		DUTY_cycleForTimers(Timer0,ValueOfLDR,0);
	}
	else if(g_DutyCycleOfRoom <= 100)
	{
		LCD_displayStringRowColumn(3,10,"100");
		DUTY_cycleForTimers(Timer0,ValueOfLDR,0);
	}
	else
	{
		LCD_displayStringRowColumn(1,10,"0 ");
		DUTY_cycleForTimers(Timer0,0,0);
	}
	/*** For timer 2***/
	if(ReceptionFalg == 0)
	{
		/*************************/
		ValueOfLDR = LDR_readChannel(CH1);
		/*********************************/
		g_DutyCycleOfReception = ((float)(ValueOfLDR / THE_MAX_DUTY_OF_LED) * 100 );
	}
	/*************************************/
	if(g_DutyCycleOfReception <= 25 && g_DutyCycleOfReception >= 20)
	{
		LCD_displayStringRowColumn(1,10,"25 ");
		DUTY_cycleForTimers(Timer2,ValueOfLDR,0);
	}
	else if(g_DutyCycleOfReception <= 50)
	{
		LCD_displayStringRowColumn(1,10,"50 ");
		DUTY_cycleForTimers(Timer2,ValueOfLDR,0);
	}
	else if(g_DutyCycleOfReception <= 75)
	{
		LCD_displayStringRowColumn(1,10,"75 ");
		DUTY_cycleForTimers(Timer2,ValueOfLDR,0);
	}
	else if(g_DutyCycleOfReception <= 100)
	{
		LCD_displayStringRowColumn(1,10,"100");
		DUTY_cycleForTimers(Timer2,ValueOfLDR,0);
	}
	else
	{
		LCD_displayStringRowColumn(1,10,"0 ");
		DUTY_cycleForTimers(Timer2,0,0);
	}
}
void SCREEN_staticLayout(void)
{
	LCD_displayStringRowColumn(0,0,"-->Reception->");
	LCD_displayStringRowColumn(1,0,"Intensity:    %");
	LCD_displayStringRowColumn(2,0,"-->Room->");
	LCD_displayStringRowColumn(3,0,"Intensity:    %");
}
