/*** Import from the HAL_Layerd ***/
#include "../HAL/LCD/lcd.h"
#include "../HAL/LM35_TEMP_SENSOR/lm35_temperature_interface.h"
#include "../HAL/DC_MOTOR/motor_interface.h"
/*** Import from the MCAL_Layerd ***/
#include "../MCAL/GLOBAL_INTERRUPT/global.h"
#include "../MCAL/INTERRUPT/interrupt_interface.h"
#include "../MCAL/ADC/adc_interface.h"
#include "../MCAL/UART/uart_interface.h"
/*** Import from the APP_Layerd ***/
#include "app_sw_components.h"
#include "util/delay.h"

/*** This object used to receive the data by UART ***/
volatile uint8 g_ReceiveDataOfUART = TURN_OFF_THE_SYSTEM;
void main(void)
{

	/*** This variable used to store the temperature ***/
	uint8 temp = LOGIC_LOW;
	/*** This variable used to store the status of LCD ***/
	uint8 ScreenStatus = LOGIC_LOW;
	/* initialize ADC driver */
	ADC_init(SENSOR_CHANNEL_ID);
	/*** close the GUI in the first ***/
	LCD_sleepMode();
	/* initialize DC_Motor */
	MOTOR_init();
	/*** Initialize The UART Drive**/
	UART_init(UART_BAUD_RATE);
	/*** Set the CallBackFunctionOfEXTINT0 ***/
	EXTERNAL_interruptSetCallBack(&CLOSE_systemFunction, EXTINT0);
	/*** Set the CallBackFunctionOfEXTINT1 ***/
	EXTERNAL_interruptSetCallBack(&OPEN_systemFunction, EXTINT1);
	/*** Set the Configuration Of EXTINT0 ***/
	ENABLE_externalInterrupt(EXTINT0,FALLING_EDGE);/* initialize EX_INTERRUPT Driver */
	/*** Set the Configuration Of EXTINT1 ***/
	ENABLE_externalInterrupt(EXTINT1,FALLING_EDGE);/* initialize EX_INTERRUPT Driver */
	/*** Enable the global interrupt for input capture unit used for ultra_sonic_sensor ***/
	GLOBAL_interruptEnable();


    while(1)
    {
    	/*** Receive the data of slave MCUs in locker system ***/
    	g_ReceiveDataOfUART = UART_receiveByte();
    	/*** The reception control Systems ***/
    	while( g_ReceiveDataOfUART == TURN_ON_THE_SYSTEM)
        {
    		/* Read ADC channel 2 where the LM35_Sensor is connected */
            temp = LM35_getTemperature();
            /*** The Screen status of displaying ***/
            if(ScreenStatus == LOGIC_LOW)
            {
            	/*** Display the Main sentences on LCD ***/
            	LCD_staticSentences();
            	/*** Change the Screen flag status ***/
            	ScreenStatus = LOGIC_HIGH;
            }
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

        LCD_sleepMode();
        ScreenStatus = LOGIC_LOW;


    }
}
