   /*****************************************************************
    *[FILE NAME] 	: Timer1_prog.c								 	*
    *											  					*
    *[AUTHOR(S)]    : OmarAhmed					  					*
    *										        				*
    *[DATE CREATED] : Oct 10, 2022						 			*
    * 										  						*
    *[DECRIPTION]   :  								  				*
    *****************************************************************/
#include "std_types.h"
#include "common_macros.h"
#include "TIMER1_interface.h"
#include "TIMER1_private.h"
#include "TIMER1_config.h"
#include "avr/interrupt.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

/*ISR FOR ICU*/
ISR(TIMER1_CAPT_vect){
	if(g_callBackPtr != NULL_PTR){
		g_callBackPtr();
		g_callBackPtr = NULL_PTR;
		 /* another method to call the function using pointer to function (*g_callBackPtr)(); */
	}
}
/*ISR FOR COMPA*/
ISR(TIMER1_COMPA_vect){
	if(g_callBackPtr != NULL_PTR){
		g_callBackPtr();
		//g_callBackPtr = NULL_PTR;
		 /* another method to call the function using pointer to function (*g_callBackPtr)(); */
	}

}
/*ISR FOR OVF*/
ISR(TIMER1_OVF_vect){
	if(g_callBackPtr != NULL_PTR){
		g_callBackPtr();
		g_callBackPtr = NULL_PTR;
		 /* another method to call the function using pointer to function (*g_callBackPtr)(); */
	}

}
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void TIMER1_init(TIMER1_Config * Config_Ptr){

	if(!(((Config_Ptr->waveform) == 15 )|| (Config_Ptr -> waveform) == 14)){
		TCCR1A = (1<<3) | (1<<2);
	}
	/*SET timer_mode*/
	TCCR1A |=((Config_Ptr->timer_mode) << 6);
	/*ASSUME NO OPERATION ON COMPARE UNIT B (TURN UNIT B OFF)*/
	CLEAR_BIT(TCCR1A,4);
	CLEAR_BIT(TCCR1A,5);
	/*SET WAVEFORM */
	TCCR1A  = (TCCR1A & 0xFC) | ((Config_Ptr->waveform)& 0x03);
	TCCR1B  = (TCCR1B & 0) 	  | (((Config_Ptr->waveform)& 0x0C) << 3);
	/*SET IF ICU MODE WAS CHOOSEN */
	TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->Non_Icu_OR_Icu_Edge) << 6 );
	/*SET INTERRUPT ENABLE OF EACH MODE*/
	SET_BIT(TIMSK,(Config_Ptr->intrrupt_mode));
	/*SET INITIAL TIMER COUNTER*/
	TCNT1 = (Config_Ptr->initial_value);
	if((Config_Ptr->intrrupt_mode) == ICU_INT_ENABLE){
		ICR1 = 0;
	}
	/*SET TOP VALUE FOR CTC MODE*/
	if((Config_Ptr->Top_CTC_Value_ELSE_0) != 0){
		OCR1A = Config_Ptr->Top_CTC_Value_ELSE_0;
	}
	/*SET CLOCK*/
	TCCR1B |=  (TCCR1B & 0xF8) | ((Config_Ptr -> clock_selector) & 0x07);
}

void TIMER1_De_init(void){
	TCCR1B = 0;
	TCCR1A = 0;
	OCR1A  = 0;
	TCNT1  = 0;
	TIMSK  = 0;
}

void TIMER1_ClearCounterValue(void){
	TCNT1 = 0;
}

void TIMER1_CTC_TOP_Value(uint16 Top_CTC ){
	OCR1A = Top_CTC;
}

uint16 TIMER1_ICU_getInputCaptureValue(void){
	return ICR1;
}

void TIMER1_ICU_SetEdgeType(TIMER1_Config * Config_Ptr){
	TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->Non_Icu_OR_Icu_Edge) << 6 );
}

void TIMER1_SetCallBack(void(*a_ptr)(void)){

	g_callBackPtr = a_ptr;
}

void TIMER1_Enable(CLOCK_SELECT clock_selector){
	TCCR1B = (TCCR1B & 0xF8) | ((clock_selector) & 0x07);
}

void TIMER1_Disable(void){
	TCCR1B = ((TCCR1B & 0xF8) | (0));

}

void EnableGlobalInterrupt(void){
	SET_BIT(SREG,7);
}

void DisableGlobalInterrupt(void){
	CLEAR_BIT(SREG,7);
}
