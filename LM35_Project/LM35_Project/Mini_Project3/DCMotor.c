   /*****************************************************************
    *[FILE NAME] 	: DCMotor.c									*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 3, 2022										*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/

#include "DCMotor.h"
#include "GPIO_interface.h"
#include "Timer0_interface.h"
void DcMotor_Init(void){
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_PIN0_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_PIN1_ID, PIN_OUTPUT);
	GPIO_writePin(MOTOR_PORT_ID,MOTOR_PIN0_ID,LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_ID,MOTOR_PIN1_ID,LOGIC_LOW);
}
void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	uint8 percentage = 0;
	switch(state){
	case MOTOR_STOP	:
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_PIN0_ID,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_PIN1_ID,LOGIC_LOW);
		break;
	case MOTOR_CW	:
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_PIN0_ID,LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_PIN1_ID,LOGIC_LOW);
		percentage  = (uint8)(((uint32)TIMER0_MAX_REG*speed)/(MOTOR_MAX_PERCENTAGE));
		PWM_Timer0_Start(percentage);
		break;
	case MOTOR_ACW	:
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_PIN0_ID,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID,MOTOR_PIN1_ID,LOGIC_HIGH);
		percentage  = (uint8)(((uint32)TIMER0_MAX_REG*speed)/(MOTOR_MAX_PERCENTAGE));
		PWM_Timer0_Start(percentage);
		break;
	}
}
