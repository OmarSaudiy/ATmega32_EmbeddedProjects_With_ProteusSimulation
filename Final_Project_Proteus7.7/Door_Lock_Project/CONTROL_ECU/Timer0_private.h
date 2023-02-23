   /*****************************************************************
    *[FILE NAME] 	: Timer0_private.h								*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 3, 2022									*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/

#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_

#define TCCR0   *((volatile uint8 * const)0x53)
#define TCNT0	*((volatile uint8 * const)0x52)
#define OCR0	*((volatile uint8 * const)0x5C)
#define TIMSK	*((volatile uint8 * const)0x59)
#define TIFR	*((volatile uint8 * const)0x58)

#endif /* TIMER0_PRIVATE_H_ */
