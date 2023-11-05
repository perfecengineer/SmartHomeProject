#include "../HAL/LDR/ldr_interface.h"
#include "../MCAL/ADC/adc_interface.h"
#include "../MCAL/GPIO/gpio.h"
#include "../HAL/LCD/lcd.h"
#include "app_sw_components.h"
#include "util/delay.h"


void main(void)
{
	uint8 Roomflag  = 0;
	uint8 Receptionflag  = 0;
	APP_initOfAllUsagePeripheral();
	SCREEN_staticLayout();
    while(1)
    {
    	LDR_controlDutyCycl(Roomflag,Receptionflag);


    }
}
