/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: WatchDog Timer Drive ********************
***************** Date:  27/8/2023 ******************************************
*/
#ifndef WATCHDOG_INTERFACE_H_
#define WATCHDOG_INTERFACE_H_
#include "../../UTILS/STD_TYPES.h"
/*** Periods of time out ***/
#define TIME_OUT_16_3_ms     0x00
#define TIME_OUT_32_5_ms     0x01
#define TIME_OUT_65_ms       0x02
#define TIME_OUT_0_13_sec    0x03
#define TIME_OUT_0_26_sec    0x04
#define TIME_OUT_0_52_sec    0x05
#define TIME_OUT_1_0_sec     0x06
#define TIME_OUT_2_1_sec     0x07
/*** Select the period ***/
//#define SELECT_TIME_OUT                TIME_OUT_1_0_sec
/*** The prototype of WDT Turn ON ***/
void WDT_ON(uint8 TimeOut);
/*** The prototype of WDT Turn Off ***/
void WDT_OFF(void);

#endif
