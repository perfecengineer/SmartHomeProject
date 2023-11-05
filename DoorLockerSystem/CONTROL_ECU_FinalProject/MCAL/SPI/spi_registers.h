/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: SPI Drive ***********************************
***************** Date:  15/9/2023 ******************************************
*/
#ifndef MCAL_SPI_SPI_REGISTERS_H_
#define MCAL_SPI_SPI_REGISTERS_H_
#include "../../UTILS/STD_TYPES.h"
/**************** Redefine the SPI registers ****************/
/*** SPI control register ***/
#define SPI_CTRL_REG         (*((volatile uint8 *)(0x2D)))
/*** SPI status register ***/
#define SPI_STATUS_REG       (*((volatile uint8 *)(0x2E)))
/*** SPI data register ***/
#define SPI_DATA_REG         (*((volatile uint8 *)(0x2F)))

#endif /* MCAL_SPI_SPI_REGISTERS_H_ */
