   /*****************************************************************
    *[FILE NAME] 	: main.c										*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 27, 2022									*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/

#include "std_types.h"
#include "common_macros.h"
#include "GPIO_interface.h"
#include "UART_interface.h"
#include "TIMER1_interface.h"
#include "LCD_interface.h"
#include "keypad.h"
#include "util/delay.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PASSWORD_NOT_MATCHED 		 0
#define PASSWORD_MATCHED 		     1

#define DOOR_NOT_CLOSED				 0
#define DOOR_CLOSED					 1

#define ERROR						 0
#define RELEASE						 1

#define CHECK_BOTH_PASS			     1
#define CHECK_SAVED_PASS			 6
#define CHECK_SAVED_TO_CHANGE		 3

#define ENTER_PRESSED				 13
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
volatile uint8 pressed_key = 0xFF;
volatile static uint8 pass_check = 0;
volatile uint8 password[15] = {0,};
volatile uint8 repassword[15] = {0,};
uint8 door_status = 0 ;


/*******************************************************************************
 *                           Functions Prototype                               *
 *******************************************************************************/
void New_Password_Menu(void);
void Main_Option_Menu(void);
void Open_Door_Menu(void);
void Change_Pass_Menu(void);
void Door_Status(void);
void Error_Password(void);

/*******************************************************************************
 *                                Main Function                                *
 *******************************************************************************/
int main (void){
	/*Initialization Scope... for better memory consumption*/
	{
	/*LCD Initialization*/
	LCD_init();
	/*Passing structure object by address to Initialize TIMER1
	 * Initialization Without Enabling the Peripheral
	 *   */
	TIMER1_Config TIMER1_Config = {NON_PWM_OC1A_Disconnected,CTC_TOP_OCR1A,NON_ICU,NO_CLK,COMP_A_INT_ENABLE,0,0};
	TIMER1_init(&TIMER1_Config);
	/*Passing structure object by address to Initialize UART  */
	UART_Config UART_Config = {DOUBLE_SPEED,Tx_Rx_Polling,Tx_Rx_Enabled,STOP_1_BIT,PARITY_DISABLED,DATA_8_BIT,RATE_9600};
	UART_init(&UART_Config);
	EnableGlobalInterrupt();
	}
	while(1){
		switch(pass_check){
		case 0  : New_Password_Menu();break;
		case 1  : Main_Option_Menu();break;
		default : break;
		}
	}
	return (0);
}
/* Setting New Password For The System*/
void New_Password_Menu(void){
	uint8 i = 0,j = 0;
	/*New Password*/
	LCD_clearScreen();
	LCD_displayString("Enter Password :");
	LCD_moveCursor(1,0);
	while((pressed_key = KEYPAD_getPressedKey()) != ENTER_PRESSED ){
		_delay_ms(350);
		password[i] = pressed_key;
		LCD_displayCharacter('*');
		i++;
	}
	_delay_ms(350);
	password[i]   = '#';
	password[i+1] = '\0';

	/*Re-Enter Same Password*/
	LCD_clearScreen();
	LCD_displayString("Re-Enter Same");
	LCD_displayStringRowColumn(1,0,"Pass :");
	while((pressed_key = KEYPAD_getPressedKey()) != ENTER_PRESSED ){
		_delay_ms(350);
		repassword[j] = pressed_key;
		LCD_displayCharacter('*');
		j++;
	}
	_delay_ms(350);
	repassword[j]   = '#';
	repassword[j+1] = '\0';

	/*Send Byte to identify The required action*/
	UART_sendByte(CHECK_BOTH_PASS);
	/*Send Password to UART*/
	UART_sendString(password);
	/*Send rePassword to UART*/
	UART_sendString(repassword);
	/*Polling till CONTROL_ECU Respond */
	while(UART_ReceiveIntrrputFlag == 0);
	/*Receive CONTROL_ECU respond*/
	pass_check = UART_receiveByte();
}

/*			Open Door or Change Password 		*/
void Main_Option_Menu(void){
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"+ : Open Door");
	LCD_displayStringRowColumn(1,0,"- : Change Pass");
	uint8 choice = KEYPAD_getPressedKey();
	_delay_ms(350);
	switch(choice){
	case '+' : Open_Door_Menu();break;
	case '-' : Change_Pass_Menu();break;
	default  : pass_check=1;break;
	}
}

/*					Open Door Menu				 */
void Open_Door_Menu(void){
	static uint8 counter = 0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Enter Password :");
	LCD_moveCursor(1,0);
	uint8 i = 0 ;
	while((pressed_key = KEYPAD_getPressedKey()) != ENTER_PRESSED ){
		_delay_ms(350);
		password[i] = pressed_key;
		LCD_displayCharacter('*');
		i++;
	}
	_delay_ms(350);
	password[i]   = '#';
	password[i+1] = '\0';

	/*Send Byte to identify The required action*/
	UART_sendByte(CHECK_SAVED_PASS);
	/*Send Password to UART*/
	UART_sendString(password);
	/*Polling till CONTROL_ECU Respond */
	while(UART_ReceiveIntrrputFlag == 0);
	/*Receive CONTROL_ECU respond*/
	pass_check = UART_receiveByte();
	/*Check CONTROL_ECU respond & act accordingly*/
	if(pass_check == PASSWORD_MATCHED){
		counter = 0;
		TIMER1_SetCallBack(&Door_Status);
		door_status = DOOR_NOT_CLOSED;
		TIMER1_CTC_TOP_Value(58594);
		TIMER1_Enable(CLK_DIV_1024);
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"Unlocking Door");
		while(door_status != DOOR_CLOSED);
		TIMER1_Disable();
		TIMER1_ClearCounterValue();
		pass_check = PASSWORD_MATCHED;
	}
	else if (pass_check == PASSWORD_NOT_MATCHED){
		if(counter >= 2){
			counter = 0;
			TIMER1_SetCallBack(&Error_Password);
			door_status = ERROR;
			TIMER1_CTC_TOP_Value(58594);
			TIMER1_Enable(CLK_DIV_1024);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Password Invalid!");
			LCD_displayStringRowColumn(1,0,"  System Locked");
			while(door_status != RELEASE);
			TIMER1_Disable();
			TIMER1_ClearCounterValue();
			pass_check = 1;
			return;
		}
		counter++;
		Open_Door_Menu();
	}
}

/*		   Change Pass Menu			*/
void Change_Pass_Menu(void){
	static uint8 counter = 0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Enter Password :");
	LCD_moveCursor(1,0);
	uint8 i = 0;
	while((pressed_key = KEYPAD_getPressedKey()) != ENTER_PRESSED ){
		_delay_ms(350);
		password[i] = pressed_key;
		LCD_displayCharacter('*');
		i++;
	}
	_delay_ms(350);
	password[i]   = '#';
	password[i+1] = '\0';
	/*Send Byte to identify The required action*/
	UART_sendByte(CHECK_SAVED_TO_CHANGE);
	/*Send Password to UART*/
	UART_sendString(password);
	/*Polling till CONTROL_ECU Respond */
	while(UART_ReceiveIntrrputFlag == 0);
	/*Receive CONTROL_ECU respond*/
	pass_check = UART_receiveByte();
	/*Check CONTROL_ECU respond & act accordingly*/
	if(pass_check == PASSWORD_MATCHED){
		counter = 0;
		pass_check = 0;
	}
	else if(pass_check == PASSWORD_NOT_MATCHED){
		if(counter >= 2){
			counter = 0;
			TIMER1_SetCallBack(&Error_Password);
			door_status = ERROR;
			TIMER1_CTC_TOP_Value(58594);
			TIMER1_Enable(CLK_DIV_1024);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Password Incorrect!");
			LCD_displayStringRowColumn(1,0,"  System Locked");
			while(door_status != RELEASE);
			TIMER1_Disable();
			TIMER1_ClearCounterValue();
			pass_check = 1;
			return;
		}
		counter++;
		Change_Pass_Menu();
	}
}

/*			Door Status Function		*/
void Door_Status(void){
	static  uint8 status = 0;
	status++;
	if(status == 2){
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"Door Unlocked");
		TIMER1_CTC_TOP_Value(23437);
	}
	else if(status == 3){
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"Door is Locking");
		TIMER1_CTC_TOP_Value(58594);
	}
	else if(status == 5){
		LCD_clearScreen();
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
	door_status = RELEASE;
	}
}
