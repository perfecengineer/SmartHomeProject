#include "sw_components.h"
#include "../UTILS/STD_TYPES.h"
#include "avr/delay.h"
#include "../HAL/STEPPER_MOTOR/stepper_interface.h"
#include "../HAL/SERVO_MOTOR/servo_interface.h"
#include "../HAL/DC_MOTOR/motor_interface.h"
#include "../HAL/LED/led_interface.h"
#include "../MCAL/SPI/spi_interface.h"
uint16 angle = 0;
uint8 COMPARE_strings(uint8* str1, uint8* str2)
{
	while( (*str1 != '\0') || (*str2 != '\0') )
	{
		if( (*str1) !=  (*str2) )
		{
			return 0;
		}
		(str1) ++;
		(str2) ++;
	}
	return 1;
}
SYSTEM_resetAllFlags(uint8* ptr1,uint8* ptr2,uint8* ptr3,uint8* ptr4)
{
	*ptr1 = 0;*ptr2 = 0;*ptr3 = 0;*ptr4 = 0;
}
void STEPPER_motorStatus(uint8 state)
{

	if(state == 1)
	{
		while(angle != 360)
		{
			STEPPER_angle(angle);
			_delay_ms(50);
			angle += 45;
		}
	}
	else
	{
		while(angle != 0)
		{
			STEPPER_angle(angle);
			_delay_ms(10);
			angle -= 45;
		}
	}
}
void DOOR_openAndCloseAllSystems(void)
{
	    /*** In first open the lock of the Door (servo_motor act as a lock)***/
		SERVO_setAngle(OPEN_LOCK);
		_delay_ms(1000);
		/*** After opened the Door lock, Turn on the stepper motor and DC motor to open the all Door ***/
		STEPPER_motorStatus(OPEN_DOOR);
		/*** Turn on the stepper motor and DC motor in clock wise direction to open the all Door ***/
		MOTOR_directon(CW);
		_delay_ms(15000);
		/***  hold the motor for 3-seconds ***/
		STOP_rotatonOfMotor();
		_delay_ms(3000);
		/*** Close the door by close the stepper_motor and DC motor ***/
		STEPPER_motorStatus(CLOSE_DOOR);
		/***  motor for 15-seconds A-CW ***/
		MOTOR_directon(ANTI_CW);
		_delay_ms(14000);
		/*** close the Door in first ***/
		STEPPER_angle(CLOSE_DOOR);
		STOP_rotatonOfMotor();
		/*** Close the Door lock by using the servo_motor ***/
		SERVO_setAngle(CLOSE_LOCK);
}
void FILL_firstArray(uint8* FirstPassWordString)
{
	/*** Stop all LEDs in start ***/
	LED_enable(PORTC_ID,PIN6,LED_OFF);
	/*** Wait until the master will be send the first password ***/
	while((SPI_sendReceiveByte(OK) != SEND_NOW));
	/*** Receive the password from master ***/
	SPI_receiveString(FirstPassWordString);
	/*** Indicate that the first password entered already ***/
	LED_enable(PORTC_ID,PIN6,LED_ON);
	/*** Stop all LEDs in start ***/
	LED_enable(PORTC_ID,PIN4,LED_OFF);
}
void LDEs_indicateErrorAtWriteOrReadInEEPROM(void)
{
	/*** Indicate that the error appear when write or read in EEPROM ***/
	LED_enable(PORTC_ID,PIN5,LED_ON);
	LED_enable(PORTC_ID,PIN6,LED_ON);
	LED_enable(PORTC_ID,PIN4,LED_ON);
}
void STOP_allLeds(void)
{
	LED_enable(PORTC_ID,PIN5,LED_OFF);
	LED_enable(PORTC_ID,PIN6,LED_OFF);
	LED_enable(PORTC_ID,PIN4,LED_OFF);
}
void TOGGLE_allLeds(void)
{
	LED_enable(PORTC_ID,PIN5,LED_TOGGLE);
	LED_enable(PORTC_ID,PIN6,LED_TOGGLE);
	LED_enable(PORTC_ID,PIN4,LED_TOGGLE);
}
