   /*****************************************************************
    *[FILE NAME] 	: ADC_private.h									*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 4, 2022									*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define	ADMUX		*((volatile uint8 * const)0x27)
#define	ADCSRA		*((volatile uint8 * const)0x26)
#define	ADC 		*((volatile const uint16 * const)0x24)
#define SFIOR 		*((volatile uint8 * const)0x50)

#endif /* ADC_PRIVATE_H_ */
