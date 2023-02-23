   /*****************************************************************
    *[FILE NAME] 	: main.c										*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 27, 2022									*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/
#include <string.h>
#include "std_types.h"
#include "common_macros.h"
#include "GPIO_interface.h"
#include "Timer0_interface.h"
#include "TIMER1_interface.h"
#include "UART_interface.h"
#include "I2C_interface.h"
#include "buzzer.h"
#include "DCMotor.h"
#include "external_eeprom.h"
#include "util/delay.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define REQ_DEFAULT					 0xFF

#define PASSWORD_NOT_MATCHED 		 0
#define PASSWORD_MATCHED 		     1

#define DOOR_NOT_CLOSED				 0
#define DOOR_CLOSED					 1

#define ERROR						 0
#define RELEASE						 1

#define CHECK_BOTH_PASS			     1
#define CHECK_SAVED_PASS			 6
#define CHECK_SAVED_TO_CHANGE		 3


#define PASSWORD_EEPROM_ADDRESS		 0x0100
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
volatile uint8 req_action = 0;
volatile uint8 password[15]= {0,};
volatile uint8 repassword[15]= {0,};
uint8 door_status = 0 ;
 uint8 counter = 0;

/*******************************************************************************
 *                           Functions Prototype                               *
 *******************************************************************************/

void Check_Both_Pass(void);
void Check_Saved_Pass(void);
void Door_Status(void);
void Error_Password(void);
void Receive_Password(void);
/*******************************************************************************
 *                                Main Function                                *
 *******************************************************************************/

int main(void){
	/*Initialization Scope... for better memory consumption		*/
	{
	/*Passing structure object by address to Initialize TIMER1
	 * Initialization Without Enabling the Peripheral
	 *   														*/
	TIMER1_Config TIMER1_Config = {NON_PWM_OC1A_Disconnected,CTC_TOP_OCR1A,NON_ICU,NO_CLK,COMP_A_INT_ENABLE,0,0};
	TIMER1_init(&TIMER1_Config);
	/*Buzzer Initialization										*/
	Buzzer_init();
	/*Passing structure object by address to Initialize I2C 	*/
	I2C_Config I2C_Config = {0x01,RATE_400Kbps};
	I2C_init(&I2C_Config);
	/*DC-Motor Initialization									*/
	DcMotor_Init();
	/*Passing structure object by address to Initialize UART 	*/
	UART_Config UART_Config = {DOUBLE_SPEED,Tx_Polling_Rx_Interrupt,Tx_Rx_Enabled,STOP_1_BIT,PARITY_DISABLED,DATA_8_BIT,RATE_9600};
	UART_init(&UART_Config);
	UART_SetCallBack(&Receive_Password);
	EnableGlobalInterrupt();
	}
	while(1){
		switch(req_action){
		case CHECK_BOTH_PASS 		: Check_Both_Pass();break;
		case CHECK_SAVED_PASS 		:
		case CHECK_SAVED_TO_CHANGE  : Check_Saved_Pass();break;
		case REQ_DEFAULT			:
		default						:break;
		}
	}

	return(0);
}

void Check_Both_Pass(void){
	uint8 str[15]={0,};
	/*Compare Both Passwords*/
	uint8 i = 0,result = strcmp(password,repassword);
	if(result == 0){
		/*  Saving Password to EEPROM  */
		while(password[i] != '\0'){
			EEPROM_writeByte((PASSWORD_EEPROM_ADDRESS+i),password[i]);
			_delay_ms(10);
			i++;
		}
		EEPROM_writeByte((PASSWORD_EEPROM_ADDRESS+i),password[i]);
		_delay_ms(10);
		/*Send Confirmation to HMI_ECU */
		UART_sendByte(PASSWORD_MATCHED);
	}
	else{
		/* Discard this password
		 * Send De-Confirmation to HMI_ECU
		 * */
		UART_sendByte(PASSWORD_NOT_MATCHED);
	}
	/* Back to default case -> while(1) & wait for next received UART Byte by interrupt
	 *
	 * */
	req_action = REQ_DEFAULT;
}

void Check_Saved_Pass(void){
	uint8 i = 0,real_password[15]={0,},result = 0;
	EEPROM_readByte((PASSWORD_EEPROM_ADDRESS+i),&real_password[i]);
	while(real_password[i] != '\0'){
		i++;
		EEPROM_readByte((PASSWORD_EEPROM_ADDRESS+i),&real_password[i]);
	}
	/*Compare received  passwords with saved EEPROM*/
	result = strcmp(password,real_password);
	/*Act according to the result of comparing passwords*/
	if(result == 0){
		counter = 0;
		/*Send Respond to HMI_ECU*/
		UART_sendByte(PASSWORD_MATCHED);
		if(req_action == CHECK_SAVED_PASS){
		TIMER1_ClearCounterValue();
		TIMER1_SetCallBack(&Door_Status);
		door_status = DOOR_NOT_CLOSED;
		TIMER1_CTC_TOP_Value(58594);
		TIMER1_Enable(CLK_DIV_1024);
		DcMotor_Rotate(MOTOR_CW,MOTOR_MAX_PERCENTAGE);
		while(door_status != DOOR_CLOSED);
		TIMER1_Disable();
		TIMER1_ClearCounterValue();
		}
		else if(req_action == CHECK_SAVED_TO_CHANGE){

		}
	}
	else{
		if(counter >= 2){
			counter = 0;
			UART_sendByte(PASSWORD_NOT_MATCHED);
			TIMER1_ClearCounterValue();
			TIMER1_SetCallBack(&Error_Password);
			door_status = ERROR;
			TIMER1_CTC_TOP_Value(58594);
			TIMER1_Enable(CLK_DIV_1024);
			DcMotor_Rotate(MOTOR_STOP,MOTOR_MAX_PERCENTAGE);
			Buzzer_on();
			while(door_status != RELEASE);
			TIMER1_Disable();
			TIMER1_ClearCounterValue();

		}
		UART_sendByte(PASSWORD_NOT_MATCHED);
		counter++;
	}
	/* Back to default case -> while(1) & wait for next received UART Byte by interrupt
	 *
	 * */
	req_action = REQ_DEFAULT;
}

/*			Door Status Function		*/
void Door_Status(void){
	static  uint8 status = 0;
	status++;
	if(status == 2){
		DcMotor_Rotate(MOTOR_STOP,MOTOR_MAX_PERCENTAGE);
		TIMER1_CTC_TOP_Value(23437);
	}
	else if(status == 3){
		DcMotor_Rotate(MOTOR_ACW,MOTOR_MAX_PERCENTAGE);
		TIMER1_CTC_TOP_Value(58594);
	}
	else if(status == 5){
		DcMotor_Rotate(MOTOR_STOP,MOTOR_MAX_PERCENTAGE);
		status = 0;
		door_status = DOOR_CLOSED;
	}
}

/*	Three consecutive Errors Function	*/
void Error_Password(void){
	static  uint8 status = 0;
	status++;
	if(status == 7){
	status = 0;
	DcMotor_Rotate(MOTOR_STOP,MOTOR_MAX_PERCENTAGE);
	Buzzer_off();
	door_status = RELEASE;
	}
}

void Receive_Password(void){
	uint8 choice = UART_receiveByte();
		/* Convert UART From Interrupt to Polling
		 * AVR Already disable GIFE at begin of ISR
		 * Just for Generality i will disable GIE
		 * */
		DisableGlobalInterrupt();
		/*Receive First Password*/
		UART_receiveString(password);
		/*Receive Second Password*/
		if(choice == CHECK_BOTH_PASS){
		UART_receiveString(repassword);
		}
		/* Convert UART From Polling to Interrupt
		 * AVR Already enable GIFE at end of ISR
		 * Just for Generality i will enable GIE
		 * */
		EnableGlobalInterrupt();
		/*Set flag to go to Check_Both_Pass()*/
		req_action = choice;
	}

