   /*****************************************************************
    *[FILE NAME] 	: ultrasonic.h									*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 10, 2022									*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ULTRASONIC_TRIGGER_PORT_ID		PORTB_ID
#define ULTRASONIC_TRIGGER_PIN_ID		PIN5_ID
#define ULTRASONIC_ECHO_PORT_ID			PORTD_ID
#define ULTRASONIC_ECHO_PIN_ID			PIN6_ID


#define PROTEUS_SOUND_SPEED_DIV_2			17283
#
/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void Ultrasonic_init(void);

uint16 Ultrasonic_readDistance(void);

#endif /* ULTRASONIC_H_ */
