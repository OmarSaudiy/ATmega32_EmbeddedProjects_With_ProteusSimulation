   /*****************************************************************
    *[FILE NAME] 	: buzzer.h										*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 27, 2022									*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_
#include "GPIO_interface.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define BUZZER_PORT_ID	PORTB_ID
#define BUZZER_PIN_ID	PIN7_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void Buzzer_init(void);

void Buzzer_on(void);

void Buzzer_off(void);


#endif /* BUZZER_H_ */
