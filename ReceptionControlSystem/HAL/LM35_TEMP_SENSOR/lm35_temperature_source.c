/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: LM35 Temperature sensor Drive ***************
***************** Date:  29/8/2023 ******************************************
*/
#include "lm35_temperature_interface.h"
uint8 LM35_getTemperature(void)
{
	uint8 tem_value = 0;
	ADC_readChannel(SENSOR_CHANNEL_ID);
	tem_value = (uint8)(((uint32)g_adcResult * SENSOR_MAX_TEMPERATURE * VOLTAGE_REFFERNCE) / (SENSOR_MAX_VOLT_VALUE * ADC_MAXIMUM_VALUE));
	return tem_value;
}

