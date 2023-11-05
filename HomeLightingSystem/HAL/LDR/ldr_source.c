/*
 * ldr_source.c
 *
 *  Created on: Oct 27, 2023
 *      Author: ACS
 */

#include "ldr_interface.h"
#include "../../MCAL/ADC/adc_interface.h"
uint8 LDR_readChannel(uint8 Channel)
{
	float32 LdrValue = NOTOK;
	if((ADC_readChannel(Channel)) == OK)
	{
		LdrValue = ((g_adcResult / THE_MAX_RESOLUTION_OF_ADC) * THE_MAX_DUTY_OF_LED);
	}
	return (LdrValue);
}
