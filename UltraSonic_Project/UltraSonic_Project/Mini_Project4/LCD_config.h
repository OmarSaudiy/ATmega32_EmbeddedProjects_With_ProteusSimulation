   /*****************************************************************
    *[FILE NAME] 	: LCD_config.h									*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 4, 2022									*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_
/*Choose one of 2 LCD Bit Mode
 *
 * 				LCD_4BIT_MODE
 * 				LCD_8BIT_MODE
 *
 * */
#define LCD_BIT_MODE 	LCD_8BIT_MODE

#define LCD_RS_PORT_ID                	 PORTB_ID
#define LCD_RS_PIN_ID                	 PIN0_ID
#define LCD_E_PORT_ID                 	 PORTB_ID
#define LCD_E_PIN_ID                  	 PIN2_ID

#if(LCD_BIT_MODE == LCD_8BIT_MODE)
#define LCD_DATA_PORT_ID				 PORTA_ID
#endif

#if(LCD_BIT_MODE == LCD_4BIT_MODE)

#define LCD_DB4_PIN_ID                 PIN3_ID
#define LCD_DB5_PIN_ID                 PIN4_ID
#define LCD_DB6_PIN_ID                 PIN5_ID
#define LCD_DB7_PIN_ID                 PIN6_ID
#endif

#endif /* LCD_CONFIG_H_ */
