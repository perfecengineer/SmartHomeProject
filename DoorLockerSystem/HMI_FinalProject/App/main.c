/**** Includes of External HW Modules ***/
#include "../HAL/LCD/lcd.h"
#include "../HAL/KEYPAD/keypad_interface.h"
#include "../HAL/ULTRA_SONIC_SENSOR/ultra_sonic_interface.h"
/**** Includes of internal Modules MCU ***/
#include "../MCAL/UART/uart_interface.h"
#include "../MCAL/SPI/spi_interface.h"
#include "../MCAL/GLOBAL_INTERRUPT/global.h"
#include "../MCAL/WDT/watchdog_interface.h"
#include "../MCAL/INTERNAL_EEPROM/eeprom.h"
/**** Includes of SW components of Application ***/
#include "util/delay.h"
#include "sw_components.h"
/*** This variable use for count the number of input digits ***/
uint8 g_NumberOfDigitOfPassWord = PASSWORD_SIZE;
/*** This variable use for count the number of incorrect input consecutive passwords ***/
uint8 g_NumberOfConsecutiveIncorrectPassword = CLEAR_OBJECT;
/*** This variable use to determine the Status of Flow Of The Main Options  ***/
uint8 g_StatusOfFlowOfTheMainOptions = CLEAR_OBJECT;
int main(void)
{
/******** This segment use to create all objects of project ***/
	/*** Array used for store the input password from user,And Assign it by any initial value ***/
	uint8 PassWordString[PASSWORD_SIZE + SERVICE_STEPS] = {CLEAR_OBJECT};
	/*** This variable use for count the number of input digits ***/
	uint8 NumberOfDigitOfPassWord = CLEAR_OBJECT;
	/*** This variable use to determine the status of LCD ***/
	uint8 FalgUseForLcdChecking = CLEAR_OBJECT;
	/*** This variable use to determine the status of WDT ***/
	uint8 FalgUseForWDT = CLEAR_OBJECT;
	/*** This variable use to determine the HW component will be use ***/
	uint8 FalgUseForHwKeypadOrVirtualTerminal = CLEAR_OBJECT;
	/*** This variable use to store input digit ***/
	uint8 InputDigit = CLEAR_OBJECT;
	/*** This variable use to determine the status of Virtual Terminal ***/
	uint8 Flag_UseForUartChecking = CLEAR_OBJECT;
	/*** This flag use to select the used system to enter the password ***/
	uint8 FlagUseToSelectRecievingSysytem = CLEAR_OBJECT;
	/*** This variable use to store the capture distance ***/
	//uint16 RequiredDistance = CLEAR_OBJECT;
	/*** This variable use to determine the LCD mode ( flag = 0 -> sleep mode,flag = 1 -> active mode) ***/
	uint8 FlagLcdMode = CLEAR_OBJECT;
	/*** This variable use to determine the status of communications. ***/
	uint8 StatusCounter = CLEAR_OBJECT;
	/*** This variable use to store the number of reset occurs ***/
	uint8 FlagStateOfPasswoeds = CLEAR_OBJECT;
	/*** This variable use to determine the status of System (log_in or sign_up) ***/
	uint8 MainSystemStatus = SETUP_THE_SYSTEM_SETTINGS;
/******** This segment use to Call all initial function for each used module ***/
	/*** initial function used to setup Keypad setting ***/
	KEYPAD_Init();
	/*** initial function used to setup UART setting ***/
	UART_init(UART_BUAD_RATE);
	/*** initial function used to setup SPI setting in master mode ***/
	SPI_initMaster();
	/*** initial function used to setup Ultrasonic_sensor ***/
	Ultrasonic_init();
	/*** Enable the global interrupt ****/
	GLOBAL_interruptEnable();
	/*** Stop the WDT in start of every cycle ***/
	WDT_OFF();
/**************************** Super loop ******************************************/
	while(1)
	{
/********************************************************************************
******************************** KeyPad system **********************************
*********************************************************************************
*/
/**** This used to determine the interfacing between the user and the system, interact with (Phone or keypad) ****/
		if(FlagUseToSelectRecievingSysytem == LOGIC_LOW)
		{
/************ Wait until the sensor reach to stable to measure the distance ****/
			while((Ultrasonic_readDistance() == LOGIC_HIGH));
			/*** Check the distance between User and door ****/
			while(Ultrasonic_readDistance() <= KEYPAD_DISTANCE)
			{
				/*** Checking the LCD mode ***/
				if(FlagLcdMode == LOGIC_LOW)
				{
					/*** Active the LCD ***/
					LCD_inAchtiveMode();
					/*** Clear the flag ***/
					FlagLcdMode = LOGIC_HIGH;
					if(MainSystemStatus == SETUP_THE_SYSTEM_SETTINGS)
						/*** This function use to Ask user to enter password on LCD ***/
						DISPLAY_onScreenEnterPassWord();
					else if(MainSystemStatus == LOG_IN_TO_SYSTEM)
						/*** Display the main option on LCD ***/
						DISPLAY_onScreenMainOptions();

				}
				/*** This condition use to determine what will display on LCD ***/
				if(FalgUseForLcdChecking == LOGIC_HIGH && MainSystemStatus == SETUP_THE_SYSTEM_SETTINGS)
				{
					/*** Display Ask user to confirm the password on LCD ***/
					DISPLAY_onScreenToConfirmEnteredPassWord();
					FalgUseForLcdChecking = LOGIC_HIGH + 1;
				}
			   /*** Capture the input digit of password from user via KeyPad ***/
			   InputDigit = KEYPAD_Get_Value();
/******** This Segment used to store the password from use digit by digit in Array ***/
			   if((InputDigit != '\0') && (NumberOfDigitOfPassWord < PASSWORD_SIZE) && (InputDigit != ENTER_KEY))
			   {
				   /********* This used to determine the status of system ****************************/
				   	if(MainSystemStatus == LOG_IN_TO_SYSTEM)
				   	{
				   		if((InputDigit == OPEN_DOOR_KEY) || (InputDigit == SETTINGS_KEY))
				   		{
					   		g_StatusOfFlowOfTheMainOptions = InputDigit;
					   		DISPLAY_onScreenEnterPassWord();
					   		InputDigit = '\0';
				   		}
				   	}
				   	if((InputDigit != '\0') && (MainSystemStatus == SETUP_THE_SYSTEM_SETTINGS || (g_StatusOfFlowOfTheMainOptions == OPEN_DOOR_KEY) || (g_StatusOfFlowOfTheMainOptions == SETTINGS_KEY)))
				   	{
				   		/*** This Segment used to determine the LCD status ***/
				   		if(FalgUseForLcdChecking == (LOGIC_HIGH + 1))
				   			LCD_moveCursor(SECOND_ROW,(COLUMN_10TH + NumberOfDigitOfPassWord));
				   		else
				   			LCD_moveCursor(SECOND_ROW,NumberOfDigitOfPassWord);
				   		/*** Display any input digit from Keypad on LCD as Astric_(*) ***/
				   		DISPLAY_onScreenAstric();
				   		/*** Store input digit from Keypad in Array ***/
				   		PassWordString[NumberOfDigitOfPassWord] = InputDigit;
				   		/*** Increment the counter of input digits by one ***/
				   		NumberOfDigitOfPassWord ++;
				   	}
			   }
/******** This Segment used to send the input password from KeyPad to ECU2 *****/
			   if((InputDigit == ENTER_KEY))
			   {
				   g_NumberOfDigitOfPassWord = NumberOfDigitOfPassWord;
					/*** Assign The 6th digit of Array by NULL_Character indicate to end of string (password) ***/
					PassWordString[g_NumberOfDigitOfPassWord + 1] = '\0';
					/*** Clear the counter of digit ,for next cycle to confirm the password ***/
					NumberOfDigitOfPassWord = CLEAR_OBJECT;
					/*** Set the flag by one ,meaning that the password is entered ************/
					FlagUseToSelectRecievingSysytem = LOGIC_HIGH;
					if(StatusCounter < 1)
					{
						/*** Checking the Status of LCD *****************/
						FalgUseForLcdChecking = LOGIC_HIGH;
					}
					else
					{
						/*** Checking the Status of LCD *****************/
						FalgUseForLcdChecking = LOGIC_LOW;
					}

					break;
			   }
			}
		}
/********************************************************************************
*********************** Virtual Terminal system *********************************
*********************************************************************************
*/
		if(FlagUseToSelectRecievingSysytem == LOGIC_LOW)
		{

			if(Flag_UseForUartChecking == LOGIC_LOW )
			{
/******** This segment use to display on LCD Or Virtual Terminal, to interact with user ***/
				/*** LCD in start in sleep mode ***/
				LCD_inSleepMode();
				if(MainSystemStatus == SETUP_THE_SYSTEM_SETTINGS)
					/*** This function use to Ask user to enter password on Virtual Terminal ***/
					DISPLAY_onVirtualTerminalEnterPassWord();
				else if(MainSystemStatus == LOG_IN_TO_SYSTEM )
					/*** This function use to display the main options on Virtual Terminal ***/
					DISPLAY_onVirtualTerminalMainOptions();
				if(FalgUseForWDT == LOGIC_LOW)
					/*** Start the Watch_dog timer to count ***/
					WDT_ON(TIME_OUT_1_0_sec);

			}
			else if(Flag_UseForUartChecking == LOGIC_HIGH && StatusCounter == LOGIC_HIGH)
			{
				/*** Display Ask user to confirm the password on Virtual Terminal ***/
				DISPLAY_onVirtualTerminalToConfirmEnteredPassWord();
			}
/************ This block used to select the option to enter the password or change the password ***/
			if(MainSystemStatus == LOG_IN_TO_SYSTEM)
			{
				/*** Receive the selected option via Virtual Terminal ***/
				g_StatusOfFlowOfTheMainOptions = UART_receiveByte();
				/*** Display receive the selected option via Virtual Terminal ***/
				UART_sendByte(g_StatusOfFlowOfTheMainOptions);
				/*** Check the input option ,Is the input option of Main options or not ***/
				if((g_StatusOfFlowOfTheMainOptions == OPEN_DOOR_KEY) || (g_StatusOfFlowOfTheMainOptions == SETTINGS_KEY))
		   		{
					/*** This function use to Ask user to enter password on Virtual Terminal ***/
					DISPLAY_onVirtualTerminalEnterPassWord();
		   		}
			}
/******** This Segment used to Send the input password from Virtual Terminal to ECU2 via SPI communication protocol ***/
			/*** Capture the input String (password) from user via Virtual Terminal ***/
			UART_receiveString(PassWordString);
			/*** Stop the watch_dogg timer ***/
			WDT_OFF();
			/*** Display the input password on Virtual Terminal ***/
			UART_sendString(PassWordString);
			/*** This condition use to determine what will display on Virtual Terminal ***/
			Flag_UseForUartChecking = LOGIC_HIGH;
			/*
			 *  Clear the last input digit (Enter Key) of input password from Virtual Terminal.
			 *  Assign The 6th digit of Array by NULL_Character indicate to end of string (password).
			 */
			PassWordString[g_NumberOfDigitOfPassWord + 1] = '\0';
			/*** Set the flag by one ,meaning that the password is entered ************/
		    FlagUseToSelectRecievingSysytem = LOGIC_HIGH;
		    /***              ****/
		    FalgUseForWDT = LOGIC_HIGH;
		}
/************************************************************************************
 * ************************ master send the data to slave ***************************
 * **********************************************************************************
 */
		/********** Master talking with the slave to receive the passwords ****/
		if(FlagUseToSelectRecievingSysytem == LOGIC_HIGH && StatusCounter < 2)
		{
			PassWordString[g_NumberOfDigitOfPassWord] = '@';
			/*** Wait until the slave to be ready to receive the password **/
			while((SPI_sendReceiveByte(SEND_NOW) != OK));
			/*** Send the input password from Virtual Terminal to ECU2 via SPI communication protocol ***/
			SPI_sendString(PassWordString);
			_delay_ms(100);
			FlagStateOfPasswoeds = SPI_sendReceiveByte(DUMMY_DATA);
			/*** Increase the counter by one , indicate that the first password is send ***/
			StatusCounter ++;
			/*** Return this flag to receive the next password ****/
			FlagUseToSelectRecievingSysytem = LOGIC_LOW;
			/*** This block for the SIGN_UP_state ***/
			if(StatusCounter == 2 && MainSystemStatus == SETUP_THE_SYSTEM_SETTINGS)
			{
				if(FlagStateOfPasswoeds == OK)
				{
					/**** Switch the system to LOG_IN state ***/
					MainSystemStatus = LOG_IN_TO_SYSTEM;
					/**** Switch the the LCD mode to display the Main options ***/
					FlagLcdMode = LOGIC_LOW;
					/**** Switch the the Virtual Terminal mode to display the Main options ***/
					Flag_UseForUartChecking = LOGIC_LOW;
					/*** Reset this flag for LOG_IN_state ***/
					StatusCounter = CLEAR_OBJECT;
				}
				else
				{
					/***          ****************  Another Solution. **************************
					 ****** Reset all objects in system ***
					SYSTEM_resetAllFlags(&FalgUseForLcdChecking,&Flag_UseForUartChecking,&FlagUseToSelectRecievingSysytem,&FlagLcdMode,&StatusCounter,&FlagStateOfPasswoeds,&MainSystemStatus);
					*
					*/
					/*** Start the Watch_dog timer to count ***/
					WDT_ON(TIME_OUT_65_ms);
					_delay_ms(100);
				}
			}
			/*** This block for the LOG_IN_state ***/
			else if(StatusCounter == 1 && MainSystemStatus == LOG_IN_TO_SYSTEM)
			{
				/*** Master wait until the slave to be ready to receive data ***/
				_delay_ms(200);
				/*** Mater send the dummy data to slave , to receive the its data ***/
				FlagStateOfPasswoeds = SPI_sendReceiveByte(g_StatusOfFlowOfTheMainOptions);
				/*** Check the status of input password ***/
				if(FlagStateOfPasswoeds == OK && g_StatusOfFlowOfTheMainOptions == OPEN_DOOR_KEY)
				{
/*** The entered password is correct, so the system will be open ***/
					/*** Display the status on the the Virtual Terminal ***/
					if(FalgUseForWDT == LOGIC_HIGH)
					{
						/*** Door open 18 seconds ***/
						VirtualTerminal_doorStatus(OPEN_DOOR);
						_delay_ms(19000);
						/*** Door close after 15 seconds ***/
						VirtualTerminal_doorStatus(CLOSE_DOOR);
						_delay_ms(15000);
					}
				/*** Display the status on the LCD ****/
					else
					{
						/*** Door open 18 seconds ***/
						LCD_doorStatus(OPEN_DOOR);
						_delay_ms(19000);
						/*** Door close after 15 seconds ***/
						LCD_doorStatus(CLOSE_DOOR);
						_delay_ms(15000);
					}
					/*** Clear the counter of consecutive incorrect input passwords ***/
					g_NumberOfConsecutiveIncorrectPassword = 0;
					/*** Reset all objects to use in the next step ***/
					RESET_toMainOptions(&FlagUseToSelectRecievingSysytem,&g_StatusOfFlowOfTheMainOptions,&FlagLcdMode,&StatusCounter,&Flag_UseForUartChecking);
				}
				else if(FlagStateOfPasswoeds == OK && g_StatusOfFlowOfTheMainOptions == SETTINGS_KEY)
				{
					/***          ****************  Another Solution. **************************
					 ** Clear the counter of consecutive incorrect input passwords
					 **
					//g_NumberOfConsecutiveIncorrectPassword = 0;
					/****** Reset all objects in system ***
					//SYSTEM_resetAllFlags(&FalgUseForLcdChecking,&Flag_UseForUartChecking,&FlagUseToSelectRecievingSysytem,&FlagLcdMode,&StatusCounter,&FlagStateOfPasswoeds,&MainSystemStatus);
					/*** Reset all objects to use in the next step ***
					//RESET_toMainOptions(&FlagUseToSelectRecievingSysytem,&g_StatusOfFlowOfTheMainOptions,&FlagLcdMode,&StatusCounter&Flag_UseForUartChecking);
					//g_StatusOfFlowOfTheMainOptions = 0;
					*/
					/*** Start the Watch_dog timer to count ***/
					WDT_ON(TIME_OUT_65_ms);
					_delay_ms(100);
				}
				else
				{
					/*** Increment the number of consecutive incorrect input passwords ***/
					g_NumberOfConsecutiveIncorrectPassword ++;
					if(g_NumberOfConsecutiveIncorrectPassword == NUMBER_PERMISSION_INCORRECT_CONSUCUTIVE_PASSWORDS)
					{
						/*** Display the error massage on LCD or Virtual Terminal, and wait 10 seconds and then return to main options ***/
						if(FalgUseForWDT == LOGIC_HIGH)
						{
							/*** Display the error massage on Virtual Terminal ***/
							VirtualTerminal_errorMassage();
						}
						else
						{
							/*** Display the error massage on LCD ***/
							LCD_errorMassage();
						}

						/*** Wait 10 seconds and try again ***/
						_delay_ms(10000);
						/*** Clear this variable for next trying ***/
						g_NumberOfConsecutiveIncorrectPassword = 0;

					}
					/*** Reset all objects to use in the next step ***/
					RESET_toMainOptions(&FlagUseToSelectRecievingSysytem,&g_StatusOfFlowOfTheMainOptions,&FlagLcdMode,&StatusCounter,&Flag_UseForUartChecking);
				}
			}
		}
	}
	return 0;
}
