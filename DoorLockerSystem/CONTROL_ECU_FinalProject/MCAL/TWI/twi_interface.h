/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: TWI Drive ***********************************
***************** Date:  25/9/2023 ******************************************
*/
#ifndef MCAL_TWI_TWI_INTERFACE_H_
#define MCAL_TWI_TWI_INTERFACE_H_
#include "../../UTILS/STD_TYPES.h"
#include "../GPIO/gpio_configuration.h"
/******** Setup some of configurations for TWI module ****/
#define TWI_SELE_FREQ_SCL        TWI_FREQ_SCL_400KBS
#define TWI_PRE_SCALER_SELECT	 TWI_CLK_1
#define TWI_INTERRUPT_STATE		 TWI_INTERRUPT_DISABLE
#define TWI_MODULE_ADDRESS_IN_SLAVE_MODE        0x02
/**** TWI PORT and Pins interface ***/
#define TWI_SDL_PORT				PORTC_ID
#define TWI_SDL_PIN		     		PIN1
#define TWI_SCL_PORT				PORTC_ID
#define TWI_SCL_PIN		    		PIN0
/**** TWI Prototype of initial function ****/
void TWI_init(void);
/**** TWI Function Prototype used for start the communication by master ****/
void TWI_start(void);
/**** TWI Function Prototype used for stop the communication by master ****/
void TWI_stop(void);
/**** TWI Function Prototype used for Write byte by master ****/
void TWI_writeByte(uint8 data);
/**** TWI Function Prototype used for Read data from slave and send ACK ****/
uint8 TWI_readByteWithACK(void);
/**** TWI Function Prototype used for Read data from slave and send NACK ****/
uint8 TWI_readByteWithNACK(void);
/**** TWI Function Prototype used to get the status of Data line  ****/
uint8 TWI_getStatus(void);


#endif /* MCAL_TWI_TWI_INTERFACE_H_ */
