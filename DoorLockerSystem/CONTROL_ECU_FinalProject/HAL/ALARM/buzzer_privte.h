/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: LED Drive ********************
***************** Date:  26/8/2023 ******************************************
*/
#ifndef BUZZER_PRIVTE_H_
#define BUZZER_PRIVTE_H_
#include "../../UTILS/STD_TYPES.h"
/*** This function use to on the led ***/
static void BUZZER_onFunction(uint8 selectPort,uint8 selectPin);
/*** This function use to off the led ***/
static void BUZZER_offFunction(uint8 selectPort,uint8 selectPin);
/*** This function use to toggle the led ***/
static void BUZZER_toggleFunction(uint8 selectPort,uint8 selectPin);

#endif
