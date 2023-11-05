/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: WatchDog Timer Drive ********************
***************** Date:  27/8/2023 ******************************************
*/
#include "Watchdog_interface.h"
#include "Watchdog_registers.h"
#include "util/delay.h"
/*** The Implementation of WDT Turn ON ***/
void WDT_ON(uint8 TimeOut)
{
	/*** Select the time out ***/
	/*** Set the enable bit ***/
	WDT_CONTROL_REG = TimeOut | WDT_TURN_ON_ENABLE_BIT;

}
/*** The Implementation of WDT Turn Off ***/
void WDT_OFF(void)
{
	/*** Set the Enable and Disable bits in the same operation ***/
	WDT_CONTROL_REG = WDT_TURN_OFF_ENABLE_BIT | WDT_TURN_ON_ENABLE_BIT;
	// Wait 4 cycles before clear the WDE bit
	_delay_us(4);
	WDT_CONTROL_REG = 0x00;

}
