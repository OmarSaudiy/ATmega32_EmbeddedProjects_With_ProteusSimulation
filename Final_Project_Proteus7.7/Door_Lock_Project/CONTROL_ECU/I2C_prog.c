   /*****************************************************************
    *[FILE NAME] 	: I2C_prog.c									*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 28, 2022									*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/

#include "std_types.h"
#include "common_macros.h"
#include "I2C_interface.h"
#include "I2C_private.h"
#include "I2C_config.h"

void I2C_init(I2C_Config * ptr)
{
    /* using zero pre-scaler TWPS=00 and F_CPU=8Mhz */
    TWBR = (ptr ->baud_Rate);
	TWSR = 0x00;

    /* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
       General Call Recognition: Off */

    TWAR = ((TWAR & 0) | ((ptr ->Address) << 1)); // my address = 0x01 :)

    TWCR = (1<<2); /* enable TWI */
}

void I2C_start(void)
{
    /*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << 7) | (1 << 5) | (1 << 2);

    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,7));
}

void I2C_stop(void)
{
    /*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << 7) | (1 << 4) | (1 << 2);
}

void I2C_writeByte(uint8 data)
{
    /* Put data On TWI data Register */
    TWDR = data;
    /*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << 7) | (1 << 2);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,7));
}

uint8 I2C_readByteWithACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << 7) | (1 << 2) | (1 << 6);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,7));
    /* Read Data */
    return TWDR;
}

uint8 I2C_readByteWithNACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << 7) | (1 << 2);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,7));
    /* Read Data */
    return TWDR;
}

uint8 I2C_getStatus(void)
{
    uint8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}
