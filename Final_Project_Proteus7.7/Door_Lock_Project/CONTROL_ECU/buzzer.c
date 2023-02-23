   /*****************************************************************
    *[FILE NAME] 	: buzzer.c										*
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
#include "buzzer.h"

void Buzzer_init(void){
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID,PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID, LOGIC_LOW);
}

void Buzzer_on(void){
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID, LOGIC_HIGH);
}

void Buzzer_off(void){
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID, LOGIC_LOW);
}
