   /*****************************************************************
    *[FILE NAME] 	: I2C_interface.h								*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 28, 2022									*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/

#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

#include "std_types.h"

/*******************************************************************************
 *                               Definitions                            	   *
 *******************************************************************************/


#define I2C_START         0x08 /* start has been sent */
#define I2C_REP_START     0x10 /* repeated start */
#define I2C_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define I2C_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define I2C_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define I2C_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define I2C_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/*
 * Assume Pre-scaler=0.thus TWBR = ((((F_CPU)/(RATE))-16)/2)
 * */

typedef enum{
	RATE_100Kbps=32,RATE_200Kbps=12,RATE_400Kbps=2
}baud_Rate;

typedef struct{
	uint8		Address;
	baud_Rate	baud_Rate;
}I2C_Config;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void I2C_init(I2C_Config * ptr);
void I2C_start(void);
void I2C_stop(void);
void I2C_writeByte(uint8 data);
uint8 I2C_readByteWithACK(void);
uint8 I2C_readByteWithNACK(void);
uint8 I2C_getStatus(void);



#endif /* I2C_INTERFACE_H_ */
