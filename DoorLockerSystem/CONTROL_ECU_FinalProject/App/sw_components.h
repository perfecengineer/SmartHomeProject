/*
 * SW_COMPONENT.h
 *
 *  Created on: Sep 30, 2023
 *      Author: ACS
 */
#ifndef APP_SW_COMPONENTS_H_
#define APP_SW_COMPONENTS_H_
#include "../UTILS/STD_TYPES.h"
/**** Usage macros ***/
#define OPEN_DOOR_KEY              ('+')
#define SETTINGS_KEY               ('-')
#define FINSHED_UPDATA_PASSWORD    (1)
#define PASSWORD_SIZE              (5)
#define CLEAR_OBJECT               (0)
#define FIRST_ROW                  (0)
#define SECOND_ROW                 (1)
#define COLUMN_10TH			       (10)
#define INDEX_0                    (0)
#define MAX_DISTANCE               (300)
#define KEYPAD_DISTANCE            (100)
#define SERVICE_STEPS              (3)
#define ARE_YOU_READY_TO_SEND_YOU        					(10)
#define I_AM_READY                       					(1)
#define SEND_NOW                         					(2)
#define SETUP_THE_SYSTEM_SETTINGS                			(0)
#define LOG_IN_TO_SYSTEM                         			(1)
#define STORAGE_ADDRESS_OF_PASSWORD_IN_EEPROM    			(0x0311)
#define DUMMY_DATA                               			(0xff)
#define CLOSE_LOCK                                			(0)
#define OPEN_LOCK 								  			(180)
#define CLOSE_DOOR             			      			    (0)
#define OPEN_DOOR          					                (1)
#define NUMBER_PERMISSION_INCORRECT_CONSUCUTIVE_PASSWORDS	(3)
#define TURN_ON_THE_SYSTEM       (1)
#define TURN_OFF_THE_SYSTEM      (0)
#define UART_BAUD_RATE           (9600)
/***** Functions Prototypes ***/
uint8 COMPARE_strings(uint8* str1,uint8* str2);
void SYSTEM_resetAllFlags(uint8* ,uint8* ,uint8* ,uint8*  );
void STEPPER_motorStatus(uint8 state);
void DOOR_openAndCloseAllSystems(void);
void FILL_firstArray(uint8* FirstPassWordString);
void LDEs_indicateErrorAtWriteOrReadInEEPROM(void);
void STOP_allLeds(void);
void TOGGLE_allLeds(void);
#endif /* APP_SW_COMPONENTS_H_ */
