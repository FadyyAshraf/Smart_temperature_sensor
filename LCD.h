/*
 * LCD.h
 *
 * Created: 5/25/2024 2:12:36 AM
 *  Author: Fady Ashraf
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "macros.h"
#include "avr/io.h"

#define Eight_Bit_Mode 0x38
#define Four_Bit_Mode 0x28
#define CLEAR_COMMAND 0x01
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80

void LCD_Init();
void LCD_SendCommand(char data);
void LCD_SendCharacter(uint8_t data);
void LCD_SendString(char *str);
void LCD_GoToRowCol(uint8_t row, uint8_t col);
void write_high_nibble(unsigned char portname,unsigned char value);
void send_falling_edge(void);



#endif /* LCD_H_ */