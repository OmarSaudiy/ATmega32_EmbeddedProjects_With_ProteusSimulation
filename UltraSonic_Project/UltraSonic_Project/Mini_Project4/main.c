/*
 * main.c
 *
 *  Created on: Oct 10, 2022
 *      Author: OmarAhmed
 */

#include "std_types.h"
#include "common_macros.h"
#include "GPIO_interface.h"
#include "LCD_interface.h"
#include "ultrasonic.h"
#include "TIMER1_interface.h"
#include "util/delay.h"


int main(void){
	uint16 distance = 0;
	LCD_init();
	Ultrasonic_init();
	LCD_displayString("Distance =   cm");
	while(1){
		distance = Ultrasonic_readDistance();
		if(distance >= 100){
			LCD_moveCursor(0,10);
			LCD_intgerToString(distance);
			_delay_ms(20);
		}
		else{
			LCD_moveCursor(0,10);
			LCD_intgerToString(distance);
			LCD_displayCharacter(' ');
			_delay_ms(20);
		}
	}
	return(0);
}
