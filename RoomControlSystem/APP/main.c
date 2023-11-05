#include "../MCAL/ADC/adc_interface.h"
#include "../HAL/LCD/lcd.h"
#include "../HAL/LM35_TEMP_SENSOR/lm35_temperature_interface.h"
#include "../HAL/DC_MOTOR/motor_interface.h"
#include "../HAL/ULTRA_SONIC_SENSOR/ultra_sonic_interface.h"
#include "../MCAL/GLOBAL_INTERRUPT/global.h"
#include "../MCAL/INTERRUPT/interrupt_interface.h"
#include "app_sw_components.h"
#include "util/delay.h"
volatile uint8 RoomStatus = LOGIC_LOW;/* initialize To determine the room status */
volatile uint8 ScreenStatus = LOGIC_LOW;/* initialize To determine the screen status */

void main(void)
{

	/*** This variable used to store the temperature ***/
	uint8 temp = 0;
	ADC_init(SENSOR_CHANNEL_ID); /* initialize ADC driver */

	SW_initFunctions();

	LCD_sleepMode();

	MOTOR_init();/* initialize DC_Motor */
	EXTERNAL_interruptSetCallBack(&ResetFunction, EXTINT0);

	ENABLE_externalInterrupt(EXTINT0,FALLING_EDGE);/* initialize EX_INTERRUPT Driver */

	Ultrasonic_init();/* initialize Ultrasonic_Driver */

	uint8 distance = LOGIC_HIGH;/* initialize To determine the distance between the person and the room's door */
	/*** Enable the global interrupt for input capture unit used for ultra_sonic_sensor ***/

	GLOBAL_interruptEnable();

    while(1)
    {
    	/*** Wait until the sensor reach to stable to measure the distance ****/
    	do{
    		distance = Ultrasonic_readDistance();
    	}while(distance == LOGIC_HIGH );
    	if((distance < MAX_DISTANCE))
    	{
        		if(ScreenStatus == LOGIC_LOW)
        		{
        			/* Display this string "ADC Value = " only once on LCD at the first row */
        			LCD_staticSentences();
        			ScreenStatus = LOGIC_HIGH;
        		}
    			/*** open the door and close it after 1 second  ***/
    			DOOR_openAndClose();
    			/*** The room in the running mode ***/
        		(RoomStatus = LOGIC_HIGH);
    	}
        if((RoomStatus == LOGIC_HIGH))
        {

            /* Read ADC channel 2 where the LM35_Sensor is connected */
            temp = LM35_getTemperature();
           	/* Display the ADC digital value every time at same position */
            LCD_moveCursor(3,6);
           	if(temp >= 100)
           	{
           		LCD_displayIntgerNumber(temp);
           	}
           	else
           	{
           		LCD_displayIntgerNumber(temp);
           		/* In case the digital value is three or two or one digits print space in the next digit place */
           		LCD_displayCharacter(' ');
           	}
           	/*** For the fan speed ***/
           	if(temp < 30)
           	{
           		LCD_moveCursor(1,5);
           		LCD_displayIntgerNumber(0);
           		LCD_displayCharacter(' ');
           		LCD_displayCharacter(' ');
           		/*** The fan is off ***/
           		STOP_rotatonOfMotor(MOTOR_1);
           		MOTOR_speed(0,MOTOR_1);
           		/*** The heater mechanism of speeds ***/
           		LCD_moveCursor(2,8);
           		MOTOR_directon(ANTI_CW,MOTOR_2);
           		if(temp  > 25)
           		{
           			MOTOR_speed(25,MOTOR_2);
           			LCD_displayString("25");
           			LCD_displayCharacter(' ');
           		}
           		else if(temp  > 20)
           		{
           			MOTOR_speed(50,MOTOR_2);
           			LCD_displayString("50");
           			LCD_displayCharacter(' ');
           		}
           		else if(temp  > 15)
           		{
           			MOTOR_speed(75,MOTOR_2);
           			LCD_displayString("75");
           			LCD_displayCharacter(' ');
           		}
           		else if(temp  > 5)
           		{
           			MOTOR_speed(100,MOTOR_2);
           			LCD_displayString("100");
           		}

           	}
           	else
           	{
           		LCD_moveCursor(2,8);
           		LCD_displayIntgerNumber(0);
           		LCD_displayCharacter(' ');
           		LCD_displayCharacter(' ');
           		/*** The heater is off ***/
           		MOTOR_speed(0,MOTOR_2);
           		STOP_rotatonOfMotor(MOTOR_2);
           		/*** The fan mechanism of speeds ***/
           		LCD_moveCursor(1,5);
           		MOTOR_directon(CW,MOTOR_1);
           		if(temp  < 60)
           		{
           			MOTOR_speed(25,MOTOR_1);
           			LCD_displayString("25");
           			LCD_displayCharacter(' ');
           		}
           		else if(temp  < 90)
           		{
           			MOTOR_speed(50,MOTOR_1);
           			LCD_displayString("50");
           			LCD_displayCharacter(' ');
           		}
           		else if(temp  < 120)
           		{
           			MOTOR_speed(75,MOTOR_1);
           			LCD_displayString("75");
           			LCD_displayCharacter(' ');
           		}
           		else
           		{
           			MOTOR_speed(100,MOTOR_1);
           			LCD_displayString("100");
           		}
           	}
        }
        else
        {
        	LCD_sleepMode();
        }



        }
}
