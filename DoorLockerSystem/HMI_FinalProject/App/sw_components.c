/*
 * SW_COMPONENT.c
 *
 *  Created on: Sep 30, 2023
 *      Author: ACS
 */
#include "sw_components.h"

#include "../HAL/LCD/lcd.h"
#include "../MCAL/UART/uart_interface.h"
#include  "../MCAL/GPIO/gpio.h"
#include  "../MCAL/GPIO/gpio_configuration.h"
void DISPLAY_onScreenEnterPassWord(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("plz enter pass:");
}
void DISPLAY_onScreenToConfirmEnteredPassWord(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("plz re-enter the:");
	LCD_moveCursor(1,0);
	LCD_displayString("same pass: ");
}
void DISPLAY_onScreenAstric(void)
{
	LCD_displayCharacter('*');
}
void DISPLAY_onScreenMainOptions(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("+ : Open Door. ");
	LCD_moveCursor(1,0);
	LCD_displayString("- : Change Pass. ");
}
void DISPLAY_onVirtualTerminalEnterPassWord(void)
{
	UART_sendString("<- Please enter password: ");
}
void DISPLAY_onVirtualTerminalToConfirmEnteredPassWord(void)
{
	UART_sendString("<- please re-enter the same password: ");
}
DISPLAY_onVirtualTerminalMainOptions(void)
{
	UART_sendString("<-------------------------------------------------------------------------------------------->");
	UART_sendString("<- For Open Door->[+]_(or) ");
	UART_sendString("_For Change Password->[-]->");
}
void LCD_inSleepMode(void)
{
	LCD_clearScreen();
	GPIO_writePort(LCD_DATA_PORT_ID,CLEAR_OBJECT);
}
void LCD_inAchtiveMode(void)
{
	/*** initial function used to setup LCD setting ***/
	LCD_init();
}
void SYSTEM_resetAllFlags(uint8* FalgUseForLcdChecking,uint8* Flag_UseForUartChecking,uint8* FlagUseToSelectRecievingSysytem,uint8* FlagLcdMode,uint8* StatusCounter,uint8* FlagStateOfPasswoeds,uint8 *MainSystemStatus)
{
	*FalgUseForLcdChecking = 0;
	*Flag_UseForUartChecking = 0;
	*FlagUseToSelectRecievingSysytem = 0;
	*FlagLcdMode = 0;
	*StatusCounter = 0;
	*FlagStateOfPasswoeds = 0;
	*MainSystemStatus = 0;
}
void LCD_doorStatus(uint8 state)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	if(state == 1)
	{
		LCD_displayString("Door is Unlocking");
	}
	else
	{
		LCD_displayString("Door is Locking");
	}
}
void VirtualTerminal_doorStatus(uint8 state)
{
	UART_sendString("<------------------------------------------------------------------------------------------->");
	if(state == 1)
	{
		UART_sendString("<-[ Door is Unlocking ]->");
	}
	else
	{
		UART_sendString("<-[ Door is Locking ]->");
	}
}
void VirtualTerminal_errorMassage(void)
{
	UART_sendString("<-------------------------------------------------------------------------------------------->");
	UART_sendString("<-[Incorrect password,Wait 10 Sec,try again].->");
}
void LCD_errorMassage(void)
{
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Error password");
	LCD_moveCursor(1,0);
	LCD_displayString("Wait 10 Sec,try ");
}
void RESET_toMainOptions(uint8* flag1,uint8* flag2,uint8* flag3,uint8* flag4,uint8* flag5)
{
	*flag1 = 0;*flag2 = 0;*flag3 = 0;*flag4 = 0;*flag5 = 0;
}
