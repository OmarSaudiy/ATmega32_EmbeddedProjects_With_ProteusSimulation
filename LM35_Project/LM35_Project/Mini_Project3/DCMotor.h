   /*****************************************************************
    *[FILE NAME] 	: DCMotor.h									*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 3, 2022										*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"

#define MOTOR_MAX_PERCENTAGE	100

#define MOTOR_PORT_ID PORTB_ID
#define MOTOR_PIN0_ID PIN0_ID
#define MOTOR_PIN1_ID PIN1_ID
typedef enum {
	MOTOR_STOP,MOTOR_CW,MOTOR_ACW
}DcMotor_State;

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);
#endif /* DCMOTOR_H_ */
