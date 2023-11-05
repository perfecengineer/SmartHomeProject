/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: WatchDog Timer Drive ********************
***************** Date:  27/8/2023 ******************************************
*/
#ifndef WATCHDOG_REGISTERS_H_
#define WATCHDOG_REGISTERS_H_
#include "../../UTILS/STD_TYPES.h"
/******* For status register of WDT ***/
#define WDT_SATATUS_REG        *((volatile uint8 *)0x54)
/****** For Watchdog reset flag bit***/
#define WDT_RESET_FLAG_BIT						0x08
/****** For control register of WDT***/
#define WDT_CONTROL_REG        *((volatile uint8 *)0x41)
/*********** Control bits definitions ***********/
#define WDT_TURN_OFF_ENABLE_BIT       			0x10
#define WDT_TURN_ON_ENABLE_BIT       			0x08
#define WDT_PRE_SCALER_BIT0                     0x01
#define WDT_PRE_SCALER_BIT1                     0x02
#define WDT_PRE_SCALER_BIT2                     0x04
#endif
