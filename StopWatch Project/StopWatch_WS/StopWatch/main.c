/*
 * main.c
 *
 *  Created on: Sep 11, 2022
 *      Author: OmarAhmed
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
unsigned char count[6]= {0,};
void Timer1_CTCInit(void){

	TCNT1 = 0;
	OCR1A = 977;
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
	TIMSK |= 1 << OCIE1A;
	SREG |= 1 << 7;
}
void All_ExtIntr_Init(void){

	MCUCR |= (1 << ISC11) | (1 << ISC10) | (1 << ISC01);
	GICR |= 0xE0;
	SREG |= 1 << 7;
}
int main(void){

	DDRC |= 0x0F;
	PORTC &= 0xF0;
	DDRA |= 0x3F;
	PORTA &= 0xC0;
	DDRB &= ~(1 << 2);
	PORTB |= 1<<2;
	DDRD &= ~(1 <<2 ) & ~(1 << 3);
	PORTD |= 1<<2;
	All_ExtIntr_Init();
	Timer1_CTCInit();
	while(1){
		for(unsigned char i = 0 ; i<6 ;i++){
			PORTA = 1 << i;
			PORTC = (PORTC & 0xF0 ) | (count[i] & 0x0F);
			_delay_ms(2);
		}
	}

	return(0);
}

ISR(TIMER1_COMPA_vect){
	SREG|= 1<<7;
	count[0]++;
	if(count[0] == 10){
		count[0] = 0;
		count[1]++;
		if(count[1] == 6){
			count[1] = 0;
			count[2]++;
			if(count[2] == 10){
				count[2] = 0;
				count[3]++;
				if(count[3] == 6){
					count[3] = 0;
					count[4]++;
					if(count[4] == 10){
						count[4] = 0;
						count[5]++;
						if(count[5] == 10)
							count[5] = 0;
					}
				}
			}
		}
	}

}

ISR(INT0_vect){
	TCNT1 = 0;
	for(unsigned char i = 0 ; i<5 ;i++){
		count[i] = 0;
	}
}
ISR(INT1_vect){
	SREG |=  1<<0 ;
	TCCR1B = 0;
}
ISR(INT2_vect){
	SREG |=  1<<0 ;
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
}
