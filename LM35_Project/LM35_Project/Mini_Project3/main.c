/*
 * main.c
 *
 *  Created on: Oct 4, 2022
 *      Author: OmarAhmed
 */

#include "std_types.h"
#include "common_macros.h"
#include "GPIO_interface.h"
#include "Timer0_interface.h"
#include "ADC_interface.h"
#include "LCD_interface.h"
#include "lm35.h"
#include "DCMotor.h"


int main(void){
	/*set PA2 as input pin*/
	GPIO_setupPinDirection(PORTA_ID,SENSOR_CHANNEL_ID,PIN_INPUT);
	/*set PB3/OC0 as output pin*/
	GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT);
	/* Declare struct of ADC_ConfigType + Initialize ADC */
	ADC_ConfigType ADC_Config = {INTERNAL_2_56,Division_8};
	ADC_init(&ADC_Config);
	/* Initialize Motor*/
	DcMotor_Init();
	/* Initialize LCD*/
	LCD_init();
	/**/
	LCD_displayStringRowColumn(0,3,"FAN IS OFF");
	LCD_displayStringRowColumn(1,3,"TEMP =    C");

	while(1){
		uint8 temp = LM35_getTemperature();
		if(temp >= 120 ){
			LCD_displayStringRowColumn(0,3,"FAN IS ON ");
			DcMotor_Rotate(MOTOR_CW,100);
		}
		else if(temp >= 90 ){
			LCD_displayStringRowColumn(0,3,"FAN IS ON ");
			DcMotor_Rotate(MOTOR_CW,75);
		}
		else if(temp >= 60 ){
			LCD_displayStringRowColumn(0,3,"FAN IS ON ");
			DcMotor_Rotate(MOTOR_CW,50);
		}
		else if(temp >= 30 ){
			LCD_displayStringRowColumn(0,3,"FAN IS ON ");
			DcMotor_Rotate(MOTOR_CW,25);

		}
		else{
			LCD_displayStringRowColumn(0,3,"FAN IS OFF");
			DcMotor_Rotate(MOTOR_STOP,0);
			Timer0_Disable();
		}
		LCD_moveCursor(1,10);
		if(temp >= 100){
			LCD_intgerToString(temp);
		}
		else{
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
	}

	return 0;
}

