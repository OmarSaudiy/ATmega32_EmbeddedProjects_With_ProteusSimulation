   /*****************************************************************
    *[FILE NAME] 	: UART_interface.h								*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 13, 2022									*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_
#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{
	NO_DOUBLE,DOUBLE_SPEED
}Double_Speed_Mode;


typedef enum{
	Tx_Rx_Polling,Tx_Interrupt_Rx_Polling,Tx_Polling_Rx_Interrupt,Tx_Rx_Interrupt
}Interrupt_Tx_Rx;


typedef enum{
	Tx_Rx_Disabled,Tx_Enabled,Rx_Enabled,Tx_Rx_Enabled
}Tx_Rx_Enable;


typedef enum{
	STOP_1_BIT,STOP_2_BIT
}Stop_Bit;

typedef enum{
	PARITY_DISABLED,EVEN_PARITY = 2,ODD_PARITY
}Parity_Mode;

typedef enum{
	DATA_5_BIT,DATA_6_BIT,DATA_7_BIT,DATA_8_BIT
}Character_Size;

typedef enum{
	RATE_9600=9600,RATE_4800=4800,RATE_14400=14400
}Baud_Rate;

typedef struct{
	Double_Speed_Mode	Speed_Mode;
	Interrupt_Tx_Rx 	Tx_Rx_Intrrupt;
	Tx_Rx_Enable		Tx_Rx_Enable;
	Stop_Bit			Stop_Bit;
	Parity_Mode			Parity_Mode;
	Character_Size		Character_Size;
	Baud_Rate			Baud_Rate;

}UART_Config;
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void UART_init(UART_Config * ptr);

void UART_sendByte(uint8 data);

uint8 UART_receiveByte(void);

void UART_sendString(const uint8 *Str);

void UART_receiveString(uint8 *Str);

uint8 UART_ReceiveIntrrputFlag(void);

void UART_ClearReceiveFlag(void);

#endif /* UART_INTERFACE_H_ */
