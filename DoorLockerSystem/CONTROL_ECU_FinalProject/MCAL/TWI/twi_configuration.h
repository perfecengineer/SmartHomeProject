/****************************************************************************
*****************************************************************************
*****************************************************************************
***************** Author: Mohamed Ashour Hassan *****************************
***************** SW_component: TWI Drive ***********************************
***************** Date:  25/9/2023 ******************************************
*/
#ifndef MCAL_TWI_TWI_CONFIGURATION_H_
#define MCAL_TWI_TWI_CONFIGURATION_H_

/*********** Rename the Bits of Control Register *******/
#define TWI_INTERRUPT_FLAG_BIT7                 7
#define TWI_ENABLE_ACK_BIT6				        0x40
#define TWI_START_CONDITION_BIT5				0x20
#define TWI_STOP_CONDITION_BIT4				    0x10
#define TWI_ENABLE_MODULE_BIT2				    0x04
#define TWI_ENABLE_INTERRUPT_BIT0               0x01
/***************************** Pre_scaler Select *********/
#define TWI_CLK_1						0
#define TWI_CLK_4						1
#define TWI_CLK_16						2
#define TWI_CLK_64						3
/****************** Some of definition of TWI module ****/
#define TWI_GENERAL_CALL_ENABLE           		  0x01
/*** SCL rate ***/
#define TWI_FREQ_SCL_100KBS 					  (100000)
#define TWI_FREQ_SCL_400KBS 					  (400000)
#define TWI_FREQ_SCL_100MBS 					  (1000000)
#define TWI_FREQ_SCL_3_4MBS 					  (34 * 100000)
/*** TWI interrupt states ***/
#define TWI_INTERRUPT_ENABLE					  (TWI_ENABLE_INTERRUPT_BIT0)
#define TWI_INTERRUPT_DISABLE					  (0x00)
/************************* The Status of TWI module ****/
/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

#endif /* MCAL_TWI_TWI_CONFIGURATION_H_ */
