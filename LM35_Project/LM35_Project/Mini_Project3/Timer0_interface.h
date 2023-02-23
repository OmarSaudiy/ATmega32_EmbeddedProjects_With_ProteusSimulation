   /*****************************************************************
    *[FILE NAME] 	: Timer0_interface.h							*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 3, 2022									*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/
#include "std_types.h"
#include "Timer0_config.h"
#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

#define TIMER0_MAX_REG			255

#define TIMER0_OVERFLOW			1
#define TIMER0_CTC				2
#define TIMER0_PWM				3

#define CTC_NORMAL_MODE 		1
#define CTC_TOGGLE_MODE 		2


#define TIMER0_NO_PRESCALER		1
#define TIMER0_PRESCALER_8		2
#define TIMER0_PRESCALER_64		3
#define TIMER0_PRESCALER_256	4
#define TIMER0_PRESCALER_1024	5

#if 	(TIMER0_MODE == TIMER0_OVERFLOW )
void Timer0_OVF_Init(void);
#elif 	(TIMER0_MODE == TIMER0_CTC )
void Timer0_CTC_Init(void);
#elif	(TIMER0_MODE == TIMER0_PWM )
void PWM_Timer0_Start(uint8 duty_cycle);
/*
void Timer0_PWM_Init(void);
*/
#endif
void Timer0_Disable(void);
#endif /* TIMER0_INTERFACE_H_ */
