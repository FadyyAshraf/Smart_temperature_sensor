/*
 * LCD.c
 *
 * Created: 5/25/2024 2:13:05 AM
 *  Author: Fady Ashraf
 */ 

#define F_CPU 8000000

#include "util/delay.h"
#include "LCD.h"

void LCD_Init()
{
	
	DDRD |=0xF0 ;
	DDRB |=0x03;
	PORTB|=(1<<PORTB0)|(1<<PORTB1);
	
	LCD_SendCommand(0x02);
	
	LCD_SendCommand(Four_Bit_Mode);

	LCD_SendCommand(CURSOR_OFF);	//Display on cursor off
	
	LCD_SendCommand(0x01);	//clear screen
	
	LCD_SendCommand(0x06);	//entry mood
}

void send_falling_edge(void)
{
	Set_Bit(PORTB,PORTB0);
	_delay_ms(1);
	Clear_Bit(PORTB,PORTB0);
}

void LCD_SendCommand(char data)
{
	write_high_nibble('D',data>>4);
	Clear_Bit(PORTB,PORTB1);

	send_falling_edge();
	write_high_nibble('D',data);
	
	Clear_Bit(PORTB,PORTB1);
	send_falling_edge();
}

void write_high_nibble(unsigned char portname,unsigned char value)
{
	value<<=4;
	switch(portname)
	{
		case 'B':
		PORTB&=0x0f;
		PORTB|=value;
		case 'C':
		PORTC&=0x0f;
		PORTC|=value;
		case 'D':
		PORTD&=0x0f;
		PORTD|=value;
	}
}

void LCD_SendCharacter(uint8_t data)
{
	write_high_nibble('D',data>>4);
	Set_Bit(PORTB,PORTB1);
	
	send_falling_edge();
	write_high_nibble('D',data);
	Set_Bit(PORTB,PORTB1);
	
	send_falling_edge();;
	_delay_ms(1);
}

void LCD_SendString(char *str)
{
	while((*str)!='\0')
	{
		LCD_SendCharacter(*str);
		str++;
	}
}

void LCD_GoToRowCol(uint8_t row, uint8_t coloumn)
{
	char data ;
	if(row>2||row<1||coloumn>16||coloumn<1)
	{
		data=0x80;		//return home
	}
	else if(row==1)
	{
		data=0x80+coloumn-1 ;
	}
	else if (row==2)
	{
		data=0xc0+coloumn-1;
	}
	LCD_SendCommand(data);
	_delay_ms(1);
}

