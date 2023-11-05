/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: SPI Drive ***********************************
***************** Date:  15/9/2023 ******************************************
*/
#ifndef MCAL_SPI_SPI_COFIGURATION_H_
#define MCAL_SPI_SPI_COFIGURATION_H_
/**************** Redefine the SPI bits registers ***********/
/**** For SPI control register ****/
#define SPI_INTERRUPT_ENABLE_BIT7            (0x80)
#define SPI_MODULE_ENABLE_BIT6               (0x40)
#define SPI_DATA_ORDER_BIT5                  (0x20)
#define SPI_SELE_MASTER_OR_SLAVE_BIT4        (0x10)
#define SPI_CLK_POLARITY_BIT3            	 (0x08)
#define SPI_CLK_PHASE_BIT2               	 (0x04)
#define SPI_SELE_CLK_BIT1               	 (0x02)
#define SPI_SELE_CLK_BIT0               	 (0x01)
/**** For SPI status register ****/
#define SPI_INTERRUPT_FLAG_BIT7                         (7)
#define SPI_DOUBLE_SPEED_IN_MASTER_MODE_BIT0            (0x01)
#endif /* MCAL_SPI_SPI_COFIGURATION_H_ */
/***** SPI Clock selection in normal speed mode ***/
#define CLK_4                (0x00)
#define CLK_16               (0x01)
#define CLK_64               (0x02)
#define CLK_128              (0x03)
#define CLK_16               (0x01)
/***** SPI Clock selection in double speed mode ***/
#define CLK_2                (0x00)
#define CLK_8                (0x01)
#define CLK_32               (0x02)
#define CLK_64               (0x03)
/*************** Some definitions using to SPI configuration ***/
/*** Select the SPI mode ***/
#define SPI_LEAD_SAMPLE_RIAS_TRAILLING_SETUP_FALL        (0x00)
#define SPI_LEAD_SETUP_RIAS_TRAILLING_SAMPLE_FALL        (SPI_CLK_PHASE_BIT2)
#define SPI_LEAD_SAMPLE_FALL_TRAILLING_SETUP_RIAS        (SPI_CLK_POLARITY_BIT3)
#define SPI_LEAD_SETUP_FALL_TRAILLING_SAMPLE_RIAS        (SPI_CLK_PHASE_BIT2 | SPI_CLK_POLARITY_BIT3)
/*** Select the SPI speed mode ***/
#define SPI_NORMAL_SPEED              (0x00)
#define SPI_DOUBLE_SPEED              (SPI_DOUBLE_SPEED_IN_MASTER_MODE_BIT0)
/*** Select the state of SPI module (master / slave ) ***/
#define SPI_MASTER_MODE              (SPI_SELE_MASTER_OR_SLAVE_BIT4)
#define SPI_SLAVE_MODE               (0x00)
/*** Select the SPI interrupt state ***/
#define SPI_INTERRUPT_ENABLE         (SPI_INTERRUPT_ENABLE_BIT7)
#define SPI_INTERRUPT_DISABLE        (0x00)
