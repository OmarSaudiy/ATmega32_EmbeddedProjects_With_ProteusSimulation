   /*****************************************************************
    *[FILE NAME] 	: Timer0_config.h								*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 3, 2022									*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/

#ifndef TIMER0_CONFIG_H_
#define TIMER0_CONFIG_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/*Choose one of the following timer0 modes
 * 				TIMER0_OVERFLOW
 * 				TIMER0_CTC
 * 				TIMER0_PWM
 * */
#define TIMER0_MODE TIMER0_PWM

#if (TIMER0_MODE == TIMER0_OVERFLOW)
/*
 * Choose overflow timer initial value [0 : 255]
 *
 * */
#define OVF_INITIAL_VALUE 0
#endif
#if (TIMER0_MODE == TIMER0_CTC)
/*
 * Choose CTC timer initial value [0 : 255]
 *
 * */
#define CTC_INITIAL_VALUE 0
/*
 * Choose CTC timer mode
 * 					OC0 disconnected ----->  CTC_NORMAL_MODE  	(assume Interrupt enabled )
 *					OC0 Toggle		 ----->	 CTC_TOGGLE_MODE	(assume Interrupt disabled)
 * */
#define CTC_MODE CTC_NORMAL_MODE
/*
 * Choose CTC timer TOP value (OCR0) [0:255]
 * 					EX : 200 ----> OCR0 = 200
 *
 * */
#define CTC_TOP_VALUE 200
#endif
/*Choose one of the following timer0 prescalers
 *				TIMER0_NO_PRESCALER
 *				TIMER0_PRESCALER_8
 *				TIMER0_PRESCALER_64
 *				TIMER0_PRESCALER_256
 *				TIMER0_PRESCALER_1024
 * */
#define TIMER0_PRESCALER TIMER0_PRESCALER_1024

#endif /* TIMER0_CONFIG_H_ */
