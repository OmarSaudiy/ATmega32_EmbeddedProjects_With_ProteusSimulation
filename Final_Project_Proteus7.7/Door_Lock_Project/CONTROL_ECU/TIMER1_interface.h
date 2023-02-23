   /*****************************************************************
    *[FILE NAME] 	: Timer1_interface.h						 	*
    *											  					*
    *[AUTHOR(S)]    : OmarAhmed					  					*
    *										        				*
    *[DATE CREATED] : Oct 10, 2022						 			*
    * 										  						*
    *[DECRIPTION]   :  								  				*
    *****************************************************************/

#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

#include "std_types.h"
/*	ASSUME OC1A IS THE ONLY ACTIVE UNIT  */
typedef enum{
	NON_PWM_OC1A_Disconnected,NON_PWM_OC1A_TOGGLE_ON_COMP,NON_PWM_OC1A_CLEAR_ON_COMP,NON_PWM_OC1A_SET_ON_CMP,
	PWM_OC1A_Disconnected=0,PWM_TOGGLE_OC1A_ON_COMPARE_OC1B_DISCONNECTED=1,PWM_OC1A_NON_INVERTING=2,PWM_OC1A_INVERTING=3,
	ICU_MODE=0
}SPECIFIC_TIMER1_MODE;

typedef enum{
	OVERFLOW_MODE,CTC_TOP_OCR1A=4,CTC_TOP_ICR1=12,PWM_TOP_ICR1=14,PWM_TOP_OCR1A=15,
	ICU_NO_WAVEFORM=0
}WAVEFORM_GENERATION_MODE;

typedef enum{
	NON_ICU,ICU_FALLING=0,ICU_RISING
}ICU_NON_ICU;

typedef enum{
	NO_CLK=0,CLK_DIV_1=1,CLK_DIV_8,CLK_DIV_64,CLK_DIV_256,CLK_DIV_1024
}CLOCK_SELECT;

typedef enum{
	ICU_INT_ENABLE = 5, COMP_A_INT_ENABLE=4,OVF_INT_ENABLE=2/*,COMP_B_INT_ENABLE=3*/
}INTERRUPT_MODE;


typedef struct{
	SPECIFIC_TIMER1_MODE timer_mode ;
	WAVEFORM_GENERATION_MODE waveform;
	ICU_NON_ICU	Non_Icu_OR_Icu_Edge;
	CLOCK_SELECT clock_selector;
	INTERRUPT_MODE intrrupt_mode;
	uint16 initial_value;
	uint16 Top_CTC_Value_ELSE_0;
}TIMER1_Config;



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


void TIMER1_init(TIMER1_Config * Config_Ptr);
void TIMER1_De_init(void);
void TIMER1_ClearCounterValue(void);
uint16 TIMER1_ICU_getInputCaptureValue(void);
void TIMER1_CTC_TOP_Value(uint16 Top_CTC );
void TIMER1_ICU_SetEdgeType(TIMER1_Config * Config_Ptr);
void TIMER1_SetCallBack(void(*a_ptr)(void));
uint8 UART_ReceiveIntrrputFlag(void);
void TIMER1_Enable(CLOCK_SELECT clock_selector);
void TIMER1_Disable(void);
void EnableGlobalInterrupt(void);
void DisableGlobalInterrupt(void);
#endif /* TIMER1_INTERFACE_H_ */
