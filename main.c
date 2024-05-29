/*
 * main.c
 *
 * Created: 5/25/2024 1:58:21 AM
 *  Author: Fady Ashraf
 */ 
#define F_CPU 8000000

#include "avr/io.h"
#include "ADC.h"
#include "LCD.h"
#include "avr/delay.h"
#include "avr/interrupt.h"

uint16_t temp, TIMER_COUNT=0;
char temp_str[3];
int main (void)
{
	DDRD=0x01;	//Motor pin
	
	LCD_Init();
	ADC_Init();
	
	//Timer
	TCNT0=0;
	OCR0A=249;	//Number of counts
	TCCR0A |=(1<<WGM01);	//CTC mode
	LCD_SendString("Temperature=");
	LCD_GoToRowCol(2,1);
	LCD_SendString("Status:");
	TCCR0B |=(1<<CS01);	//prescaler value to (CK/8)
	TIMSK0 |=(1<<OCIE0A);
	sei();
	
	while (1)
	{
		if(TIMER_COUNT>=4000)
		{
			Clear_Bit(PORTD,0);
			while(temp>30)
			{
				temp=ADC_read(0)*(500.0/1023.0);
				SEND_TO_LCD(temp);
			}
			TIMER_COUNT=0;
			TCNT0=0;
		}
		temp=ADC_read(0)*(500.0/1024.0);
		snprintf(temp_str, 3 , "%u", temp);
		SEND_TO_LCD(temp_str);
		
		if (temp>30)
		{
			Set_Bit(PORTD,0);	//motor on
			LCD_GoToRowCol(2,8);
			LCD_SendString("HOT ");
		}
		else if(temp<=30)
		{
			Clear_Bit(PORTD,0);	//motor off
			TCNT0=0;
			TIMER_COUNT=0;
			LCD_GoToRowCol(2,8);
			LCD_SendString("COOL");
		}
	}
}

void SEND_TO_LCD(uint16_t temp)
{
	LCD_GoToRowCol(1,13);
	LCD_SendString(temp_str);
	LCD_SendCharacter(0XDF);  //degree symbol
	LCD_SendCharacter('c');
}

ISR(TIMER0_COMPA_vect)
{
	TIMER_COUNT++;
}