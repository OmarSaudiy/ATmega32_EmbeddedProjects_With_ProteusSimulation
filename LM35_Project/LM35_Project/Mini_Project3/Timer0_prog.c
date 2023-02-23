   /*****************************************************************
    *[FILE NAME] 	: Timer0_prog.c									*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 3, 2022									*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/


#include "common_macros.h"
#include "Timer0_interface.h"
#include "Timer0_config.h"
#include "Timer0_private.h"

#if 	(TIMER0_MODE == TIMER0_OVERFLOW )
void Timer0_OVF_Init(void){
	TCNT0 = OVF_INITIAL_VALUE;
	SET_BIT(TIMSK,0);
	TCCR0 = (1<<7)|(TIMER0_PRESCALER_1024);
}
#elif 	(TIMER0_MODE == TIMER0_CTC )
void Timer0_CTC_Init(void){
	TCNT0 = CTC_INITIAL_VALUE;
	OCR0  = CTC_TOP_VALUE;
#if (CTC_MODE == CTC_NORMAL_MODE)
	SET_BIT(TIMSK,1);
	TCCR0 = 0; /*Clear register before first access*/
#endif

#if (CTC_MODE == CTC_TOGGLE_MODE)
	TCCR0 = 0; /*Clear register before first access*/
	TCCR0 = (1<<4);
#endif
	TCCR0 |= (1 << 7)|(1<<3)|TIMER0_PRESCALER;

}
#elif	(TIMER0_MODE == TIMER0_PWM )
						/*M.T implementation */
void PWM_Timer0_Start(uint8 duty_cycle){

	TCNT0 = 0; //Set Timer Initial value

	OCR0  = duty_cycle; // Set Compare Value

	//DDRB  = DDRB | (1<<PB3); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<6) | (1<<3) | (1<<5) | (1<<1);
}
/*						MY_implementation
void Timer0_PWM_Init(void){

}
*/
#endif
void Timer0_Disable(void){
	TCCR0 = 0;
}
