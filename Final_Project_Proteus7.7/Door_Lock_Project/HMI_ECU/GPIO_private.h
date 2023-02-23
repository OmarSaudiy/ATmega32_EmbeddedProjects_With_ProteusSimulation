   /*****************************************************************
    *[FILE NAME] 	: GPIO_private.h									*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 3, 2022										*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/

#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define DDRA  	*((volatile uint8 * const)0x3A)
#define DDRB	*((volatile uint8 * const)0x37)
#define DDRC	*((volatile uint8 * const)0x34)
#define DDRD	*((volatile uint8 * const)0x31)

#define PORTA  	*((volatile uint8 * const)0x3B)
#define PORTB	*((volatile uint8 * const)0x38)
#define PORTC	*((volatile uint8 * const)0x35)
#define PORTD	*((volatile uint8 * const)0x32)

#define PINA  	*((volatile const uint8 * const)0x39)
#define PINB	*((volatile const uint8 * const)0x39)
#define PINC	*((volatile const uint8 * const)0x33)
#define PIND	*((volatile const uint8 * const)0x30)



#endif /* GPIO_PRIVATE_H_ */
