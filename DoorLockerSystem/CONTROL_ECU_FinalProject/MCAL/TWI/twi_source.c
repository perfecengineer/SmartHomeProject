/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: TWI Drive ***********************************
***************** Date:  25/9/2023 ******************************************
*/
#include "twi_registers.h"
#include "twi_configuration.h"
#include "twi_interface.h"
#include "../GPIO/gpio.h"
/**** TWI Implementation of initial function ****/
void TWI_init(void)
{
	/**** Setup the TWI pins direction ****/
	/**** Output in master mode ***/
	GPIO_setupPinDirection(TWI_SCL_PORT,TWI_SCL_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(TWI_SDL_PORT,TWI_SDL_PIN,PIN_OUTPUT);
	/**** Setup the clock rate of SCL and The Pre_scaler = 0 ****/
	TWI_BIT_RATE_REG = (((uint16)(F_CPU)) / ((16 + 2 * TWI_SELE_FREQ_SCL * 4)));
	TWI_STATUS_REG = TWI_PRE_SCALER_SELECT;
	/*** Setup the module address ***/
	/*** This address used in slave mode ***/
	TWI_SLAVE_ADDRESS_REG = TWI_MODULE_ADDRESS_IN_SLAVE_MODE;
	/*** Enable the TWI module ***/
	TWI_CONTROL_REG = (TWI_ENABLE_MODULE_BIT2) | (TWI_INTERRUPT_STATE);
}
/**** TWI Function Implementation used for start the communication by master ****/
void TWI_start(void)
{
    /*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
	TWI_CONTROL_REG = (1 << TWI_INTERRUPT_FLAG_BIT7) | (TWI_ENABLE_MODULE_BIT2) | (TWI_START_CONDITION_BIT5);
	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while(!((TWI_CONTROL_REG >> TWI_INTERRUPT_FLAG_BIT7) & 0x01));
}
/**** TWI Function Implementation used for stop the communication by master ****/
void TWI_stop(void)
{
    /*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
	TWI_CONTROL_REG = (1 << TWI_INTERRUPT_FLAG_BIT7) | (TWI_ENABLE_MODULE_BIT2) | (TWI_STOP_CONDITION_BIT4);
}
/**** TWI Function Implementation used for Write byte by master ****/
void TWI_writeByte(uint8 data)
{
	/*** Set the data in TWI data register ***/
	TWI_DATA_REG = data;
    /*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWI_CONTROL_REG = (1 << TWI_INTERRUPT_FLAG_BIT7) | (TWI_ENABLE_MODULE_BIT2);
	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while(!((TWI_CONTROL_REG >> TWI_INTERRUPT_FLAG_BIT7) & 0x01));
}
/**** TWI Function Implementation used for Read data from slave and send ACK ****/
uint8 TWI_readByteWithACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
	TWI_CONTROL_REG = (1 << TWI_INTERRUPT_FLAG_BIT7) | (TWI_ENABLE_MODULE_BIT2) | (TWI_ENABLE_ACK_BIT6);
	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while(!((TWI_CONTROL_REG >> TWI_INTERRUPT_FLAG_BIT7) & 0x01));
	return TWI_DATA_REG;
}
/**** TWI Function Implementation used for Read data from slave and send NACK ****/
uint8 TWI_readByteWithNACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending NACK after reading or receiving data TWEA=0
	 * Enable TWI Module TWEN=1
	 */
	TWI_CONTROL_REG = (1 << TWI_INTERRUPT_FLAG_BIT7) | (TWI_ENABLE_MODULE_BIT2);
	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while(!((TWI_CONTROL_REG >> TWI_INTERRUPT_FLAG_BIT7) & 0x01));
	return TWI_DATA_REG;
}
/**** TWI Function Implementation used to get the status of Data line  ****/
uint8 TWI_getStatus(void)
{
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	uint8 StatusValue = TWI_STATUS_REG & (0xF8);
	return StatusValue;
}

