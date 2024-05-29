/*
 * ADC.c
 *
 * Created: 5/25/2024 1:59:32 AM
 *  Author: Fady Ashraf
 */ 

#include "ADC.h"
#include "avr/interrupt.h"
#include "stddef.h"


void ADC_Init()
{
	ADMUX |= (1 << REFS0);
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
}

unsigned char ADC_read(uint16_t channel)
{
	channel &=0x07;
	ADMUX = (ADMUX|channel);
	ADCSRA |= (1 << ADSC);
	while ((ADCSRA & (1 << ADIF))==0);
	ADCSRA |= (1<<ADIF);
	return ADC;
}
