/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: SPI Drive ***********************************
***************** Date:  15/9/2023 ******************************************
*/
#include "spi_configuration.h"
#include "spi_interface.h"
#include "spi_registers.h"
#include "../../MCAL/GPIO/gpio.h"
#if SPI_MODULE_MODE        ==         SPI_MASTER_MODE
/*** Implementation of function use to enable the SPI Master ***/
void SPI_initMaster(void)
{
	/*** Setup the SPI PORT and the Pins directions ***/
	GPIO_setupPinDirection(SPI_PORT_CLK_SOURCE,SPI_PIN_CLK_SOURCE,PIN_OUTPUT);
	GPIO_setupPinDirection(SPI_PORT_SLAVE_SELE,SPI_PIN_SLAVE_SELE,PIN_OUTPUT);
	GPIO_setupPinDirection(SPI_PORT_MOSI,SPI_PIN_MOSI,PIN_OUTPUT);
	GPIO_setupPinDirection(SPI_PORT_MISO,SPI_PIN_MISO,PIN_INPUT);
	/*** Setup the setting by write in control register ***/
	SPI_CTRL_REG =  SPI_INTERRUPT_STATE | SPI_MODULE_MODE | SPI_SAMLPING_SETUP_STATE | SPI_CLK_SELECT | SPI_MODULE_ENABLE_BIT6;
	SPI_STATUS_REG  |= SPI_TRANSFER_SPEED_MODE;
}
#elif SPI_MODULE_MODE        ==         SPI_SLAVE_MODE
/*** Implementation of function use to enable the SPI Slave ***/
void SPI_initSlave(void)
{
	/*** Setup the SPI PORT and the Pins directions ***/
	GPIO_setupPinDirection(SPI_PORT_CLK_SOURCE,SPI_PIN_CLK_SOURCE,PIN_INPUT);
	GPIO_setupPinDirection(SPI_PORT_SLAVE_SELE,SPI_PIN_SLAVE_SELE,PIN_INPUT);
	GPIO_setupPinDirection(SPI_PORT_MOSI,SPI_PIN_MOSI,PIN_INPUT);
	GPIO_setupPinDirection(SPI_PORT_MISO,SPI_PIN_MISO,PIN_OUTPUT);
	/*** Setup the setting by write in control register ***/
	SPI_CTRL_REG =  SPI_INTERRUPT_STATE | SPI_MODULE_MODE | SPI_SAMLPING_SETUP_STATE | SPI_CLK_SELECT | SPI_MODULE_ENABLE_BIT6;
	SPI_STATUS_REG  |= SPI_TRANSFER_SPEED_MODE;
}
#endif
/*** Implementation of function use to Send and Receive byte ***/
uint8 SPI_sendReceiveByte(uint8 data)
{
	/* Initiate the communication and send data by SPI */
	SPI_DATA_REG = data;
	/*
	 * Wait at transfer complete.
	 * Note: SPIF flag is cleared by first reading SPSR (with SPIF set) which is done in the previous step.
	 * and then accessing SPDR like the below line.
	 */
	while(!((SPI_STATUS_REG >> SPI_INTERRUPT_FLAG_BIT7) & 0x01));
	/*** Receive the data from another SPI module ***/
	return SPI_DATA_REG;
}
/*** Implementation of function use to Send string ***/
uint8 SPI_sendString(uint8 *str)
{
	uint8 DumyData = 0;
	while((*str) != '\0')
	{
		DumyData = SPI_sendReceiveByte((*str));
		str ++;
	}
	return DumyData;
}
/*** Implementation of function use to Receive string ***/
void SPI_receiveString(uint8 *str)
{
	do{
		(*str) = SPI_sendReceiveByte(SPI_DEFAULT_DUMY_VALUE);
		str ++;
	}while(*(str -1) != '@');
	/*** Indicate the end of received string ***/
	*(str -1) = '\0';
}
