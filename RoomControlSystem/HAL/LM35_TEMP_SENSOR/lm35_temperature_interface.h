/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: LM35 Temperature sensor Drive ***************
***************** Date:  29/8/2023 ******************************************
*/

#ifndef LM35_TEMPERATURE_INTERFACE_H_
#define LM35_TEMPERATURE_INTERFACE_H_
#include "../../UTILS/STD_TYPES.h"
#include "../../MCAL/ADC/adc_interface.h"
#define SENSOR_CHANNEL_ID         CH0
#define SENSOR_MAX_VOLT_VALUE     1.5
#define SENSOR_MAX_TEMPERATURE    150


uint8 LM35_getTemperature(void);




#endif /* LM35_TEMPERATURE_INTERFACE_H_ */
