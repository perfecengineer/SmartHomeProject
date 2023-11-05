/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: Ultra_sonic_sensor Drive ********************
***************** Date:  26/9/2023 ******************************************
*/
#ifndef HAL_ULTRA_SONIC_SENSOR_ULTRA_SONIC_INTERFACE_H_
#define HAL_ULTRA_SONIC_SENSOR_ULTRA_SONIC_INTERFACE_H_
#include "../../UTILS/STD_TYPES.h"
extern volatile uint8 check;
/*** Setup the Triggered pin port and pin ***/
#define TRIGGERED_PORT                   PORTA_ID
#define TRIGGERED_PIN                    PIN7
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void Ultrasonic_init(void);
uint16 Ultrasonic_readDistance(void);





#endif /* HAL_ULTRA_SONIC_SENSOR_ULTRA_SONIC_INTERFACE_H_ */
