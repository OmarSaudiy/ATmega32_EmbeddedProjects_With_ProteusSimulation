   /*****************************************************************
    *[FILE NAME] 	: ultrasonic.c									*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 10, 2022									*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/

#include "std_types.h"
#include "common_macros.h"
#include "GPIO_interface.h"
#include "TIMER1_interface.h"
#include "ultrasonic.h"
#include <util/delay.h>

static uint8 count = 0;
static uint16 hightime = 0;



void static Ultrasonic_Trigger(void){
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,LOGIC_LOW);
}
/*PROTEUS ASSUME SOUND SPEED = 34567 CM PER SECOND
 * Then  34567 / 2 = 17283
 * (17283)*(CLK_DIV/F_CPU) = (17283)*(8/8000000)=
 *
 * */
uint16 Ultrasonic_readDistance(void){
	Ultrasonic_Trigger();
	if(count == 2){
		uint16 distance =(hightime/58);
		count = 0;
		return distance;
	}
	//return distance;
}

void static Ultrasonic_edgeProcessing(void){

	if(count == 0){
		TIMER1_ICU_SetEdgeType(ICU_FALLING);
		TIMER1_ClearCounterValue();
		count++;
	}
	else if (count == 1){
		hightime = TIMER1_ICU_getInputCaptureValue();
		TIMER1_ClearCounterValue();
		TIMER1_ICU_SetEdgeType(ICU_RISING);
		count++;
	}

}

void Ultrasonic_init(void){
	TIMER1_Config ICU_Config ={ICU_MODE,ICU_NO_WAVEFORM,ICU_RISING,CLK_DIV_8,ICU_INT_ENABLE};
	TIMER1_init(&ICU_Config);
	TIMER1_SetCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT_ID,ULTRASONIC_TRIGGER_PIN_ID,PIN_OUTPUT);
}
