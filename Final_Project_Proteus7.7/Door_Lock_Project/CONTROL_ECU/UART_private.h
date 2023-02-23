   /*****************************************************************
    *[FILE NAME] 	: UART_private.h								*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 13, 2022									*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define	UDR			*((volatile uint8 * const)0x2C)
#define	UCSRA		*((volatile uint8 * const)0x2B)
#define	UCSRB		*((volatile uint8 * const)0x2A)
#define	UCSRC		*((volatile uint8 * const)0x40)
#define	UBRRL		*((volatile uint8 * const)0x29)
#define	UBRRH		*((volatile uint8 * const)0x40)
 	 	 	 /* THE FOLLOWING IS FATAL MISTAKE  */
//#define	UBRR		*((volatile uint16 * const)0x29)

#endif /* UART_PRIVATE_H_ */
