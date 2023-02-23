   /*****************************************************************
    *[FILE NAME] 	: Timer1_config.h							 	*
    *											  					*
    *[AUTHOR(S)]    : OmarAhmed					  					*
    *										        				*
    *[DATE CREATED] : Oct 10, 2022						 			*
    * 										  						*
    *[DECRIPTION]   :  								  				*
    *****************************************************************/

#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_


#define TCCR1A	*((volatile uint8 * const)0x4F)
#define TCCR1B	*((volatile uint8 * const)0x4E)
#define TCNT1	*((volatile uint16 * const)0x4C)
#define OCR1A	*((volatile uint16 * const)0x4A)
#define OCR1B	*((volatile uint16 * const)0x48)
#define ICR1	*((volatile uint16 * const)0x46)
#define TIMSK	*((volatile uint8 * const)0x59)
#define TIFR	*((volatile uint8 * const)0x58)

#define SREG  	*((volatile uint16 * const)0x5F)

#endif /* TIMER1_PRIVATE_H_ */
