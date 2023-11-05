/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: EEPROM Drive ***********************************
***************** Date:  25/9/2023 ******************************************
*/
#include "../../MCAL/TWI/twi_configuration.h"
#include "eeprom_interface.h"
#include "avr/delay.h"
/**** Function Implementation used for write of EEPROM ***/
uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data)
{
	/* Send the Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_START)
        return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_writeByte((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR;

    /* Send the required memory location address */
    TWI_writeByte((uint8)(u16addr));
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;

    /* write byte to eeprom */
    TWI_writeByte(u8data);
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;

    /* Send the Stop Bit */
    TWI_stop();

    return SUCCESS;
}
/**** Function Implementation used for read of EEPROM ***/
uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data)
{
	/* Send the Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_START)
        return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR;

    /* Send the required memory location address */
    TWI_writeByte((uint8)(u16addr));
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;

    /* Send the Repeated Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_REP_START)
        return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    TWI_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7) | 1));
    if (TWI_getStatus() != TWI_MT_SLA_R_ACK)
        return ERROR;

    /* Read Byte from Memory without send ACK */
    *u8data = TWI_readByteWithNACK();
    if (TWI_getStatus() != TWI_MR_DATA_NACK)
        return ERROR;

    /* Send the Stop Bit */
    TWI_stop();

    return SUCCESS;
}
uint8 EEPROM_writeString(uint16 u16StratAddress,uint8* string)
{
	uint8 counter = 0;
	uint8 ErrorState = 0;
	while(string[counter] != '\0')
	{
		ErrorState = EEPROM_writeByte((u16StratAddress + counter),string[counter]);
		_delay_ms(10);
		counter ++;
	}
	return ErrorState;
}
/**** Function Prototype used for read string of EEPROM ***/
uint8 EEPROM_readString(uint16 u16StratAddress,uint8* string)
{
	uint8 counter = 0;
	uint8 ErrorState = 1;
	do
	{
		ErrorState = EEPROM_readByte((u16StratAddress + counter),(string + counter));
		_delay_ms(10);
		counter ++;
	}while(string[counter - 1] != '\0');
	/*** Store the NULL_Character ***/
	string[counter - 1] = '\0';
	return ErrorState;
}
