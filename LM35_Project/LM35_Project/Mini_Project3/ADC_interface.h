   /*****************************************************************
    *[FILE NAME] 	: ADC_interface.h								*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 4, 2022									*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include "std_types.h"


#define	ADC_REF_VOLT_VALUE	 2.56
#define ADC_MAXIMUM_VALUE    1023

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
	AREF=0,AVCC=1,INTERNAL_2_56=3
}ADC_ReferenceVolatge;

typedef enum
{
	Division_2=1,Division_4,Division_8,Division_16,Division_32,Division_64,Division_128
}ADC_Prescaler;

typedef struct{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void ADC_init(const ADC_ConfigType * Config_Ptr);

uint16 ADC_readChannel(uint8 channel_num);
#endif /* ADC_INTERFACE_H_ */
