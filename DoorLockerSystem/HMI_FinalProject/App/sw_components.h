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
#define ENTER_KEY		           ('=')
#define OPEN_DOOR_KEY              ('+')
#define SETTINGS_KEY               ('-')
#define UART_BUAD_RATE             (9600)
#define FINSHED_UPDATA_PASSWORD    (1)
#define PASSWORD_SIZE              (5)
#define CLEAR_OBJECT               (0)
#define FIRST_ROW                  (0)
#define SECOND_ROW                 (1)
#define COLUMN_10TH			       (10)
#define INDEX_0                    (0)
#define MAX_DISTANCE               (300)
#define KEYPAD_DISTANCE            (100)
#define SERVICE_STEPS                            			(3)
#define ARE_YOU_READY_TO_SEND_YOU                			(10)
#define I_AM_READY                              		 	(1)
#define SEND_NOW                                 			(2)
#define SETUP_THE_SYSTEM_SETTINGS                			(0)
#define LOG_IN_TO_SYSTEM                         			(1)
#define DUMMY_DATA                               			(0xff)
#define OPEN_DOOR								 			(1)
#define CLOSE_DOOR                               			(0)
#define NUMBER_PERMISSION_INCORRECT_CONSUCUTIVE_PASSWORDS	(3)
/***** Functions Prototypes ***/
void DISPLAY_onScreenEnterPassWord(void);
void DISPLAY_onScreenToConfirmEnteredPassWord(void);
void DISPLAY_onVirtualTerminalEnterPassWord(void);
void DISPLAY_onVirtualTerminalToConfirmEnteredPassWord(void);
void DISPLAY_onVirtualTerminalMainOptions(void);
void DISPLAY_onScreenMainOptions(void);
void DISPLAY_onScreenAstric(void);
void LCD_inSleepMode(void);
void LCD_inAchtiveMode(void);
void LCD_doorStatus(uint8 state);
void LCD_errorMassage(void);
void VirtualTerminal_doorStatus(uint8 state);
void VirtualTerminal_errorMassage(void);
void SYSTEM_resetAllFlags(uint8* ,uint8* ,uint8* ,uint8* ,uint8*,uint8*,uint8* );
void RESET_toMainOptions(uint8* flag1,uint8* flag2,uint8* flag3,uint8* flag4,uint8* flag5);

#endif /* APP_SW_COMPONENTS_H_ */
