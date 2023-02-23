   /*****************************************************************
    *[FILE NAME] 	: UART_prog.c									*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 13, 2022									*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/

#include "std_types.h"
#include "common_macros.h"
#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"
#include "avr/interrupt.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(USART_RXC_vect){
	if(g_callBackPtr != NULL_PTR){
		g_callBackPtr();
		//g_callBackPtr = NULL_PTR;
		 /* another method to call the function using pointer to function (*g_callBackPtr)(); */
	}
}


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void UART_init(UART_Config * ptr){
	UCSRA = ((ptr->Speed_Mode)<<1);
	UCSRB = (((ptr->Tx_Rx_Intrrupt) & 0x03) << 6);
	UCSRB = ((UCSRB) & 0xE7) | (((ptr->Tx_Rx_Enable) & 0x03) << 3);
	SET_BIT(UCSRC,7);
	UCSRC = ((ptr->Character_Size) << 1);
	UCSRC = (UCSRC & 0xCF) | (((ptr->Parity_Mode) & 0x03) << 4);
	UCSRC = (UCSRC & 0xF7) | ((ptr->Stop_Bit) << 3);
	UCSRC = (UCSRC & 0xF9) | (((ptr->Character_Size) & 0x03) << 1);
	CLEAR_BIT(UCSRC,7);
	if((ptr->Speed_Mode) == NO_DOUBLE){
		UBRRH = (((F_CPU/(16UL*(ptr->Baud_Rate)))-1) >>8);
		UBRRL = ((F_CPU/(16UL*(ptr->Baud_Rate)))-1);
	}
	else if((ptr->Speed_Mode) == DOUBLE_SPEED){
		UBRRH = (((F_CPU/(8UL*(ptr->Baud_Rate)))-1) >>8);
		UBRRL = ((F_CPU/(8UL*(ptr->Baud_Rate)))-1);

	}
	else{
		/*RETURN ERROR*/
	}
}

void UART_sendByte(uint8 data){
	while(BIT_IS_CLEAR(UCSRA,5));
	UDR = data;
}

uint8 UART_receiveByte(void){
	while(BIT_IS_CLEAR(UCSRA,7));
	return UDR;
}

void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}
	*******************************************************************/
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_receiveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_receiveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}

void UART_SetCallBack(void(*a_ptr)(void)){

	g_callBackPtr = a_ptr;
}

uint8 UART_ReceiveIntrrputFlag(void){
	return GET_BIT(UCSRA,7);
}

void UART_ClearReceiveFlag(void){
	SET_BIT(UCSRA,7);
}


