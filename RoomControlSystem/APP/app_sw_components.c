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

extern volatile uint8 RoomStatus;
extern volatile uint8 ScreenStatus;
void SW_initFunctions(void)
{
	GPIO_setupPinDirection(PORTB_ID,PIN4,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN5,PIN_OUTPUT);

	GPIO_setupPinDirection(PORTB_ID,PIN6,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN7,PIN_OUTPUT);

}
void DOOR_openAndClose(void)
{
	GPIO_writePin(PORTB_ID,PIN4,LOGIC_HIGH);
	GPIO_writePin(PORTB_ID,PIN6,LOGIC_HIGH);
	GPIO_writePin(PORTB_ID,PIN5,LOGIC_LOW);
	GPIO_writePin(PORTB_ID,PIN7,LOGIC_LOW);
	_delay_ms(100);
	GPIO_writePin(PORTB_ID,PIN5,LOGIC_HIGH);
	GPIO_writePin(PORTB_ID,PIN7,LOGIC_HIGH);
	GPIO_writePin(PORTB_ID,PIN6,LOGIC_LOW);
	GPIO_writePin(PORTB_ID,PIN4,LOGIC_LOW);
	_delay_ms(100);
	GPIO_writePin(PORTB_ID,PIN5,LOGIC_LOW);
	GPIO_writePin(PORTB_ID,PIN7,LOGIC_LOW);
	GPIO_writePin(PORTB_ID,PIN6,LOGIC_LOW);
	GPIO_writePin(PORTB_ID,PIN4,LOGIC_LOW);

}
void ResetFunction(void)
{
	/*** Open and close the door ***/
	DOOR_openAndClose();
	/*** Set the LCD in sleep mode ***/
	//LCD_sleepMode();
	/*** reset the running flag  ***/
	RoomStatus = LOGIC_LOW;
	/*** reset the LCD flag  ***/
	ScreenStatus = LOGIC_LOW;
}
void LCD_staticSentences(void)
{
	LCD_init(); /* initialize LCD driver */
	LCD_clearScreen();
	LCD_moveCursor(0,5);
	LCD_displayString("Room: 1");
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

	GPIO_writePort(PORTB_ID,0x00);
}
