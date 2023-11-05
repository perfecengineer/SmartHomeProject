/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: SPI Drive ***********************************
***************** Date:  15/9/2023 ******************************************
*/
#ifndef MCAL_SPI_SPI_INTERFACE_H_
#define MCAL_SPI_SPI_INTERFACE_H_
#include "../../UTILS/STD_TYPES.h"
#include "../../MCAL/GPIO/gpio_configuration.h"
/*** SPI setting configuration ***/
#define SPI_TRANSFER_SPEED_MODE       SPI_NORMAL_SPEED
#define SPI_INTERRUPT_STATE           SPI_INTERRUPT_DISABLE
#define SPI_MODULE_MODE               SPI_SLAVE_MODE
#define SPI_SAMLPING_SETUP_STATE      SPI_LEAD_SAMPLE_RIAS_TRAILLING_SETUP_FALL
#define SPI_CLK_SELECT                CLK_4
#define SPI_DEFAULT_DUMY_VALUE		  0xFF
/*** SPI interface PORT and PINS   ****/
#define SPI_PORT_CLK_SOURCE           PORTB_ID
#define SPI_PIN_CLK_SOURCE            PIN7
#define SPI_PORT_SLAVE_SELE           PORTB_ID
#define SPI_PIN_SLAVE_SELE            PIN4
#define SPI_PORT_MOSI                 PORTB_ID
#define SPI_PIN_MOSI                  PIN5
#define SPI_PORT_MISO                 PORTB_ID
#define SPI_PIN_MISO                  PIN6
#if SPI_MODULE_MODE        !=         SPI_SLAVE_MODE
/*** Prototype of function use to enable the SPI Master ***/
void SPI_initMaster(void);
#else
/*** Prototype of function use to enable the SPI Slave ***/
void SPI_initSlave(void);
#endif
/*** Prototype of function use to Send and Receive byte ***/
uint8 SPI_sendReceiveByte(uint8 data);
/*** Prototype of function use to Send string ***/
uint8 SPI_sendString(uint8 *str);
/*** Prototype of function use to Receive string ***/
void SPI_receiveString(uint8 *str);
#endif /* MCAL_SPI_SPI_INTERFACE_H_ */
