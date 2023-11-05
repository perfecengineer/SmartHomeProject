#ifndef INTERRUPT_INTREFACE_H
#define INTERRUPT_INTERFACE_H
/*******************Calling the module, that contain of standerd data types********/
#include"../../UTILS/STD_TYPES.h"
/************************ Include the contain of configuration file: **********/
#include"interrupt_configuration.h"


/************************* External interrupt sources*************************/

#define EXT0_SELECTION        			     ENABLE
#define EXT1_SELECTION                       ENABLE
#define EXT2_SELECTION                       DISABLE

/************************* Edge selection for each interrupt source************/
#if EXT0_SELECTION   ==                      ENABLE

#define ACTIVE_INTERNAL_PULL_UP_FOR_EXT0     ENABLE

#endif
/***************************************************************************/
#if EXT1_SELECTION           ==              ENABLE

#define ACTIVE_INTERNAL_PULL_UP_FOR_EXT1     ENABLE

#endif
/***************************************************************************/
#if EXT2_SELECTION           ==              ENABLE

#define ACTIVE_INTERNAL_PULL_UP_FOR_EXT2     DISABLE

#endif

/************************** function that anable the external interrupt sources:*****/
uint8 ENABLE_externalInterrupt(uint8 select_INT, uint8 select_EDGE);
/***************************function that disable the external interrupt sources:***/
uint8 DISABLE_externalInterrupt(uint8 SELECTION_INT);
/************** Set callback function provided to App****************/
uint8 EXTERNAL_interruptSetCallBack(void (* Local_ptrTOfunc)(void),uint8 select_INT);
#endif
