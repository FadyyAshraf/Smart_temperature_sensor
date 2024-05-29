/*
 * ADC.h
 *
 * Created: 5/25/2024 1:58:33 AM
 *  Author: Fady Ashraf
 */ 

#include "stddef.h"
#include "avr/io.h"

#ifndef ADC_H_
#define ADC_H_

void ADC_Init();

unsigned char ADC_read(uint16_t channel);


#endif /* ADC_H_ */