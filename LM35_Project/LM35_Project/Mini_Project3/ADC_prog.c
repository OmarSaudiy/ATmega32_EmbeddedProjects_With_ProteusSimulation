   /*****************************************************************
    *[FILE NAME] 	: ADC_prog.c									*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 4, 2022									*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/

#include "common_macros.h"
#include "ADC_interface.h"
//#include "ADC_private.h"
#include "ADC_config.h"
#include "avr/io.h"
#include "GPIO_interface.h"

void ADC_init(const ADC_ConfigType * Config_Ptr){
	ADMUX   = ((Config_Ptr->ref_volt)<<6);
	ADCSRA  = ((Config_Ptr->prescaler));
	ADCSRA |= 1<<7;
}

uint16 ADC_readChannel(uint8 channel_num){
	ADMUX = (ADMUX & 0xF8) | channel_num;
	ADCSRA |= 1<<6;
	while(GET_BIT(ADCSRA,4) != 1);
	SET_BIT(ADCSRA,4);
	return ADC;
}
