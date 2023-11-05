/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: Ultra_sonic_sensor Drive ********************
***************** Date:  26/9/2023 ******************************************
*/
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/ICU/icu.h"
#include "../ULTRA_SONIC_SENSOR/ultra_sonic_interface.h"
#include "util/delay.h"
/**** Prototype of Statics functions ***/
static void Ultrasonic_Trigger(void);
static void Ultrasonic_edgeProcessing(void);
static volatile uint16 g_Time_Wave = 0;
void Ultrasonic_init(void)
 {
	/*** The initial configurations ***/
	Icu_ConfigType g_IcuInitConfiguration = {F_CPU_8,RISING};
	/*** Setup the ICU configurations ***/
	Icu_init(&g_IcuInitConfiguration);
	/*** Setup the SetCallBack function by Ultrasonic_edgeProcessing ***/
	Icu_setCallBack(&Ultrasonic_edgeProcessing);
	/*** Set the direction of Trigger pin ***/
	GPIO_setupPinDirection(TRIGGERED_PORT,TRIGGERED_PIN,PIN_OUTPUT);
 }
static void Ultrasonic_Trigger(void)
 {
	 GPIO_writePin(TRIGGERED_PORT,TRIGGERED_PIN,LOGIC_HIGH);
	 _delay_us(15);
	 GPIO_writePin(TRIGGERED_PORT,TRIGGERED_PIN,LOGIC_LOW);
 }
 uint16 Ultrasonic_readDistance(void)
 {
	 static uint8 distance = 0;
	 /*** Set the Trigger pin ***/
	 Ultrasonic_Trigger();
	/*** Get the Distance ***/
	distance = (((g_Time_Wave) / 58) + 1);
	return distance;

 }
 static void Ultrasonic_edgeProcessing(void)
 {
	static uint8 flag = 0;
	 if(flag == 0)
	 {
		 /*** Clear the timer register ***/
		 Icu_clearTimerValue();
		 /*** Set the detection edge in the next time ***/
		 Icu_setEdgeDetectionType(FALLING);
		 /*** Set the flag to one ***/
		 flag = 1;
	 }
	 else if(flag == 1)
	 {
		 /*** Capture the value of timer ***/
		 g_Time_Wave = Icu_getInputCaptureValue();
		 /*** Set the ICU configurations ***/
		 Icu_setEdgeDetectionType(RISING);
		 /*** Set the flag to zero ***/
		 flag = 0;

	 }
 }

