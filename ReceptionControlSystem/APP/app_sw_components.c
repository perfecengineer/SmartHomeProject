/*
 * app_sw_components.c
 *
 *  Created on: Oct 22, 2023
 *      Author: ACS
 */
#include "util/delay.h"
#include "app_sw_components.h"
#include "../MCAL/GPIO/gpio.h"
#include "../HAL/LCD/lcd.h"
extern volatile uint8 g_ReceiveDataOfUART;
void CLOSE_systemFunction(void)
{
	g_ReceiveDataOfUART = TURN_OFF_THE_SYSTEM;
}
void OPEN_systemFunction(void)
{
	g_ReceiveDataOfUART = TURN_ON_THE_SYSTEM;
}
void LCD_staticSentences(void)
{
	LCD_init(); /* initialize LCD driver */
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("-->Reception<--");
	LCD_moveCursor(1,0);
	LCD_displayString("FAN:        %");
	LCD_moveCursor(2,0);
	LCD_displayString("HEATER:     %");
	LCD_moveCursor(3,0);
	LCD_displayString("Temp =      C");
}
void LCD_sleepMode(void)
{
	LCD_init(); /* initialize LCD driver */
	LCD_clearScreen();

}
