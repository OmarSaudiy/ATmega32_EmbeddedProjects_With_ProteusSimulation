   /*****************************************************************
    *[FILE NAME] 	: GPIO_prog.c									*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 3, 2022									*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/


#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "common_macros.h"
#include "GPIO_config.h"



   /*****************************************************************
    *[Function Name] : 	GPIO_setupPinDirection						*
    *																*
    *[Description]   :	Setup Direction for single pin in port		*
    *																*
    *[Args] 	     : 												*
    *	  				uint8   port_num							*
    *	 				uint8   pin_num								*
    *[Return] 	     :	void   										*
    *****************************************************************/
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num,
		GPIO_PinDirectionType direction) {

	if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS)) {
		/* Do Nothing */
	} else {
		/* Setup the pin direction as required */
		switch (port_num) {
		case PORTA_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRA, pin_num);
			} else {
				CLEAR_BIT(DDRA, pin_num);
			}
			break;
		case PORTB_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRB, pin_num);
			} else {
				CLEAR_BIT(DDRB, pin_num);
			}
			break;
		case PORTC_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRC, pin_num);
			} else {
				CLEAR_BIT(DDRC, pin_num);
			}
			break;
		case PORTD_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRD, pin_num);
			} else {
				CLEAR_BIT(DDRD, pin_num);
			}
			break;
		}
	}
}

   /*****************************************************************
    *[Function Name] : 	GPIO_writePin								*
    *																*
    *[Description]   :	Write Single pin in port by 1 or 0			*
    *																*
    *[Args] 	     : 												*
    *	  				uint8   port_num							*
    *	 				uint8   pin_num								*
    *					uint8   value								*
    *[Return] 	     :	void   										*
   ------------------------------------------------------------------*/
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value) {
	if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS)) {
		/* Do Nothing */
	} else {
		switch (port_num) {
		case PORTA_ID:
			if (value == LOGIC_HIGH) {
				SET_BIT(PORTA, pin_num);
			} else {
				CLEAR_BIT(PORTA, pin_num);
			}
			break;
		case PORTB_ID:
			if (value == LOGIC_HIGH) {
				SET_BIT(PORTB, pin_num);
			} else {
				CLEAR_BIT(PORTB, pin_num);
			}
			break;
		case PORTC_ID:
			if (value == LOGIC_HIGH) {
				SET_BIT(PORTC, pin_num);
			} else {
				CLEAR_BIT(PORTC, pin_num);
			}
			break;
		case PORTD_ID:
			if (value == LOGIC_HIGH) {
				SET_BIT(PORTD, pin_num);
			} else {
				CLEAR_BIT(PORTD, pin_num);
			}
			break;
		}
	}
}


/****************************************************************
 *[Function Name] : 	GPIO_readPin							*
 *																*
 *[Description]   :	read Pin  by 1 or 0							*
 *																*
 *[Args] 	     : 												*
 *	  				uint8   port_num							*
 *	 				uint8   value								*
 *[Return] 	     :	void		   								*
 ****************************************************************/

uint8 GPIO_readPin(uint8 port_num, uint8 pin_num){
	if((port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT)){
			/* RETURN Error*/
		}
		else{
			switch(port_num){
			case PORTA_ID : return GET_BIT(PINA,pin_num);break;
			case PORTB_ID : return GET_BIT(PINB,pin_num);break;
			case PORTC_ID : return GET_BIT(PINC,pin_num);break;
			case PORTD_ID : return GET_BIT(PIND,pin_num);break;
			}
		}
}

   /*****************************************************************
    *[Function Name] : 	GPIO_setupPortDirection						*
    *																*
    *[Description]   :	Setup Whole Port Direction 					*
    *																*
    *[Args] 	     : 												*
    *	  				uint8   port_num							*
    *	 				GPIO_PortDirectionType   direction			*
    *[Return] 	     :	void   										*
    *****************************************************************/
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction){
	if (port_num >= NUM_OF_PORTS) {
		/* RETURN Error*/
	}
	else {

		switch (port_num) {
		case PORTA_ID:
			DDRA = direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRC = direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;
		}
	}
}

/*****************************************************************
 *[Function Name] : 	GPIO_writePort							 *
 *																 *
 *[Description]   :	Write whole port by 1 or 0					 *
 *																 *
 *[Args] 	     : 												 *
 *	  				uint8   port_num							 *
 *	 				uint8   value								 *
 *[Return] 	     :	void		   								 *
 *****************************************************************/
void GPIO_writePort(uint8 port_num, uint8 value) {
	if (port_num >= NUM_OF_PORTS) {
		/* Do Nothing */
	} else {
		/* Setup the port direction as required */
		switch (port_num) {
		case PORTA_ID:
			PORTA = value;
			break;
		case PORTB_ID:
			PORTB = value;
			break;
		case PORTC_ID:
			PORTC = value;
			break;
		case PORTD_ID:
			PORTD = value;
			break;
		}
	}
}



/****************************************************************
 *[Function Name] : 	GPIO_readPort						    *
 *																*
 *[Description]   :	read whole port 							*
 *																*
 *[Args] 	     : 												*
 *	  				uint8   port_num							*
 *[Return] 	     :	uint8   									*
 ****************************************************************/

uint8 GPIO_readPort(uint8 port_num){
	if(port_num >= NUM_OF_PORTS){
		/* RETURN Error*/
	}
	else{
		switch(port_num){
		case PORTA_ID : return PINA;break;
		case PORTB_ID : return PINB;break;
		case PORTC_ID : return PINC;break;
		case PORTD_ID : return PIND;break;
		}
	}
}
