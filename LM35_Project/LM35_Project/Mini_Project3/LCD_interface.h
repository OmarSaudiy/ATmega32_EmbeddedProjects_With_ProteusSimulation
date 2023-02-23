   /*****************************************************************
    *[FILE NAME] 	: LCD_interface.h								*
    *																*
    *[AUTHOR(S)]    : OmarAhmed										*
    *																*
    *[DATE CREATED] : Oct 4, 2022									*
    * 																*
    *[DECRIPTION]   :  												*
   	*****************************************************************/

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#include "std_types.h"


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_init(void);

void LCD_sendCommand(uint8 command);

void LCD_displayCharacter(uint8 data);

void LCD_displayString(const char *Str);

void LCD_moveCursor(uint8 row,uint8 col);

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);

void LCD_intgerToString(int data);

void LCD_clearScreen(void);

#endif /* LCD_INTERFACE_H_ */
