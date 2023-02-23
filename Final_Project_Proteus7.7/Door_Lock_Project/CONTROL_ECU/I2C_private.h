   /*****************************************************************
    *[FILE NAME] 	: I2C_private.h									*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 28, 2022										*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/

#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

#define TWBR  	*((volatile uint8 * const)0x20)
#define TWCR  	*((volatile uint8 * const)0x56)
#define TWSR  	*((volatile uint8 * const)0x21)
#define TWDR  	*((volatile uint8 * const)0x23)
#define TWAR  	*((volatile uint8 * const)0x22)

#endif /* I2C_PRIVATE_H_ */
