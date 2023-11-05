/**** Includes of External HW Modules ***/
#include "../HAL/LCD/lcd.h"
//#include "../HAL/ULTRA_SONIC_SENSOR/ultra_sonic_interface.h"
#include "../HAL/EX_EEPROM/eeprom_interface.h"
#include "../HAL/LED/led_interface.h"
#include "../HAL/SERVO_MOTOR/servo_interface.h"
#include "../HAL/STEPPER_MOTOR/stepper_interface.h"
#include "../HAL/DC_MOTOR/motor_interface.h"
#include "../HAL/ALARM/buzzer_interface.h"
/**** Includes of internal Modules MCU ***/
#include "../MCAL/SPI/spi_interface.h"
#include "../MCAL/TWI/twi_interface.h"
#include "../MCAL/WDT/watchdog_interface.h"
#include "../MCAL/UART/uart_interface.h"
/**** Includes of SW components of Application ***/
#include "util/delay.h"
#include "sw_components.h"
/*** This variable use for count the number of incorrect input consecutive passwords ***/
uint8 g_NumberOfConsecutiveIncorrectPassword = 0;
/*** This variable use to determine the Status of Flow Of The Main Options  ***/
uint8 g_StatusOfFlowOfTheMainOptions = CLEAR_OBJECT;
int main(void)
{
/******** This segment use to create all objects of project ***/
	/*** Array used for store the first input password from user,And Assign it by zero as initial value ***/
	uint8 FirstPassWordString[PASSWORD_SIZE + SERVICE_STEPS] = {CLEAR_OBJECT};
	/*** Array used for store the second input password from user,And Assign it by zero as initial value ***/
	uint8 SecondPassWordString[PASSWORD_SIZE + SERVICE_STEPS] = {CLEAR_OBJECT};
	/*** This variable use to determine the status of communications until the master start send the data ***/
	//uint8 Flag_UseForStartChecking = CLEAR_OBJECT;
	/*** This variable use to determine the status of communications. ***/
	uint8 StatusCounter = CLEAR_OBJECT;
	/*** This variable use to determine the status of System (log_in or sign_up) ***/
	uint8 MainSystemStatus = SETUP_THE_SYSTEM_SETTINGS;
	/*** This variable use to determine the status of received passwords ***/
	uint8 StatusReceivedPasswords = CLEAR_OBJECT;
/******** This segment use to Call all initial function for each used module ***/
	/*** initial function used to setup SPI setting in slave mode ***/
	SPI_initSlave();
	/*** initial function used to setup Stepper_Motor ***/
	STEPPER_init();
	/*** initial function used to setup DC_Motor ***/
	MOTOR_init();
	/*** initial function used to setup Servo_motor ***/
	SERVO_init();
	/*** initial function used to setup TWI Protocol ****/
	TWI_init();
	/*** Initialize The UART Drive**/
	UART_init(UART_BAUD_RATE);
	/*** close the Door in first ***/
	STEPPER_angle(CLOSE_DOOR);
	STOP_rotatonOfMotor();
	/*** close the lock in first ***/
	SERVO_setAngle(CLOSE_LOCK);
	/*** initial functions used to setup the indication LEDs ***/
	LED_initForPin(PORTC_ID,PIN5);
	LED_initForPin(PORTC_ID,PIN6);
	LED_initForPin(PORTC_ID,PIN4);
	/*** initial function used to setup the Alarm ***/
	BUZZER_initForPin(PORTC_ID,PIN7);
	/*** Stop the WDT in start of every cycle ***/
	WDT_OFF();
///////////////////////////////////////////////
	LCD_init();
	while(1)
	{
		/*** Status of the system in start SIGN_UP To setup the password ****/
		if(MainSystemStatus == SETUP_THE_SYSTEM_SETTINGS)
		{
			/*** Wait until the master will be send to me this massage -> 'Are you ready ' ***/
			if(StatusCounter == LOGIC_LOW)
			{
				/*** Store the the first password in this object ***/
				FILL_firstArray(FirstPassWordString);
				/*** Increment the counter used to count number of received password by one ***/
				StatusCounter ++;

				LCD_moveCursor(0,5);
				LCD_displayString(FirstPassWordString);
				LCD_displayIntgerNumber(2);
			}
			else if(StatusCounter == LOGIC_HIGH)
			{
				/*** Stop all LEDs in start ***/
				LED_enable(PORTC_ID,PIN4,LED_OFF);
				LED_enable(PORTC_ID,PIN6,LED_OFF);
				/*** Wait until the master will be send the second password ***/
				while((SPI_sendReceiveByte(OK) != SEND_NOW));
				/*** Receive the password from master ***/
				SPI_receiveString(SecondPassWordString);
				/*** Compare the two received password, Store the status of comparing in this variable ***/
				StatusReceivedPasswords = COMPARE_strings(FirstPassWordString,SecondPassWordString);
				/*** Send the Passwords states after tracking ***/
				SPI_sendReceiveByte(StatusReceivedPasswords);
				/*** Increment the counter used to count number of received password by one ***/
				StatusCounter ++;
				/*** Indicate that the second password entered already ***/
				LED_enable(PORTC_ID,PIN6,LED_ON);
				///////////////////////////////////////////
				LCD_moveCursor(1,5);
				LCD_displayString(SecondPassWordString);
				LCD_displayIntgerNumber(3);
			}
			else if(StatusCounter == 2)
			{
				/*** Stop all LEDs in start ***/
				STOP_allLeds();
				if(StatusReceivedPasswords == OK)
				{
					/*** Store the password in EEPROM, From address (STORAGE_ADDRESS_OF_PASSWORD_IN_EEPROM) to (STORAGE_ADDRESS_OF_PASSWORD_IN_EEPROM + PASS_SIZE) ***/
					if(EEPROM_writeString(STORAGE_ADDRESS_OF_PASSWORD_IN_EEPROM,SecondPassWordString))
					{
						/*** Indicate that the two inputs passwords are same and store any one of them in EEPROM ***/
						LED_enable(PORTC_ID,PIN5,LED_ON);
/////////////////////////////////////////////////////////
						LCD_clearScreen();
						LCD_moveCursor(1,1);
						LCD_displayString(SecondPassWordString);

						/*** Switch the system to LOG_IN ***/
						_delay_ms(10);
						MainSystemStatus = LOG_IN_TO_SYSTEM;
						StatusCounter = LOGIC_LOW;
					}
					else
					{
						/*** Indicate that the error appear when write in EEPROM ***/
						LDEs_indicateErrorAtWriteOrReadInEEPROM();
					}
				}
				else
				{
					/***          ****************  Another Solution. **************************
					 *  Indicate that the two inputs passwords are not same
					LED_enable(PORTC_ID,PIN4,LED_ON);
					/****** Reset all objects in system
					//SYSTEM_resetAllFlags(&Flag_UseForStartChecking,&StatusCounter,&StatusReceivedPasswords,&MainSystemStatus);
					***/
					//Indicate that the two inputs passwords are not same
					LED_enable(PORTC_ID,PIN4,LED_ON);
					/*** Start the Watch_dog timer to count ***/
					WDT_ON(TIME_OUT_65_ms);
					_delay_ms(100);
				}
			}

		}
/*** Status of the system, LOG_IN To System by enter  the password ****/
		else if(MainSystemStatus == LOG_IN_TO_SYSTEM)
		{
			if(StatusCounter == LOGIC_LOW)
			{
				/*** Store the the input password in this object ***/
				FILL_firstArray(FirstPassWordString);
				/*** Change the state of the Status flag to check the input password ***/
				StatusCounter = LOGIC_HIGH;

///////////////////////////////////////////////////////////
				LCD_clearScreen();
				LCD_moveCursor(0,0);
				LCD_displayString(FirstPassWordString);
			}
			else if(StatusCounter == LOGIC_HIGH)
			{
				/*** Stop all LEDs in start ***/
				LED_enable(PORTC_ID,PIN4,LED_OFF);
				LED_enable(PORTC_ID,PIN6,LED_OFF);
				LCD_moveCursor(0,11);
				LCD_displayIntgerNumber(6);
				if(EEPROM_readString(STORAGE_ADDRESS_OF_PASSWORD_IN_EEPROM,SecondPassWordString))
				{
					/*** Wait until the master will be send the second password ***/
					LCD_moveCursor(0,12);
					LCD_displayIntgerNumber(7);
					/*** Compare the two received password, Store the status of comparing in this variable ***/
					StatusReceivedPasswords = COMPARE_strings(FirstPassWordString,SecondPassWordString);
					/*** Wait until master send the data ***/
					do
					{
						/*** Slave send to master the status of input password and the master send to slave the status of main options ***/
						g_StatusOfFlowOfTheMainOptions = SPI_sendReceiveByte(StatusReceivedPasswords);
					}while((g_StatusOfFlowOfTheMainOptions != OPEN_DOOR_KEY) && (g_StatusOfFlowOfTheMainOptions != SETTINGS_KEY));
					/*** Reset the counter that used to count number of received password by one ***/
					StatusCounter = LOGIC_LOW;
					/*** Indicate that the second password entered already ***/
					LED_enable(PORTC_ID,PIN6,LED_ON);
					LED_enable(PORTC_ID,PIN5,LED_OFF);

					LCD_moveCursor(1,0);
					LCD_displayString(SecondPassWordString);

					_delay_ms(100);
					if(StatusReceivedPasswords == OK && g_StatusOfFlowOfTheMainOptions == OPEN_DOOR_KEY)
					{
						/*** Indicate that the second password entered already and the door will be open ***/
						LED_enable(PORTC_ID,PIN5,LED_ON);
						/*** Open and Close the door in the certain period ***/
						DOOR_openAndCloseAllSystems();
						/*** Active the reception system to turn on.***/
						UART_sendByte(TURN_ON_THE_SYSTEM);


						////////////////////////////////////////////////////////////
						LCD_clearScreen();
						LCD_moveCursor(1,1);
						LCD_displayString("DONE");
					}
					else if(StatusReceivedPasswords == OK && g_StatusOfFlowOfTheMainOptions == SETTINGS_KEY)
					{
						/***          ****************  Another Solution. **************************
						 * ** Reset all objects in system
						**SYSTEM_resetAllFlags(&Flag_UseForStartChecking,&StatusCounter,&StatusReceivedPasswords,&MainSystemStatus);
						*/
						/*** Start the Watch_dog timer to count ***/
						WDT_ON(TIME_OUT_65_ms);
						_delay_ms(100);
					}
					else
					{
						/*** Stop all LEDs ***/
						STOP_allLeds();
						/*** Indicate that the input password incorrect ***/
						LED_enable(PORTC_ID,PIN4,LED_ON);
						/*** Count the number of consecutive incorrect input passwords ***/
						g_NumberOfConsecutiveIncorrectPassword ++;
						/*** if the number of consecutive incorrect input passwords be equal to 3 times, execute this block. ***/
						if(g_NumberOfConsecutiveIncorrectPassword == NUMBER_PERMISSION_INCORRECT_CONSUCUTIVE_PASSWORDS)
						{
							/*** Wait 10 seconds and try again ***/
							/*** Toggle LED every 1 second ***/
							LED_enable(PORTC_ID,PIN4,LED_ON);
							/*** Active the buzzer for 1 minute ***/
							BUZZER_enable(PORTC_ID,PIN7,BUZZER_ON);
							/*** Clear this variable for next trying ***/
							g_NumberOfConsecutiveIncorrectPassword = 0;
							_delay_ms(10000);
							/*** Disable the buzzer ***/
							BUZZER_enable(PORTC_ID,PIN7,BUZZER_OFF);
							/*** Stop all LEDs ***/
							STOP_allLeds();
						}


						///////////////////////////////
						LCD_clearScreen();
						LCD_moveCursor(1,1);
						LCD_displayString("Error");
					}

				}
				else
				{
					/*** Indicate that the error appear when write in EEPROM ***/
					LDEs_indicateErrorAtWriteOrReadInEEPROM();
				}

			}


		}


	}
	return 0;
}

