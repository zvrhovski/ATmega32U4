/*
 * adc.cpp
 *
 * Created: 8.1.2020. 15:30:37
 *  Author: Zoran
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"


// inicijalizacija adc pretvorbe
void adc_init()
{
	// postavi referencu
	ADMUX &= ~ADC_REFERENCE_MASK;
	ADMUX |= ADC_REFERENCE;
	
	// postavi djelitelj frekvencije
	ADCSRA &= ~ADC_PRESCALE_MASK;
	ADCSRA |=  ADC_PRESCALE;
	
	// omogu?i adc pretvorbu
	ADCSRA |= (1 << ADEN);
}



uint16_t adc_read(uint8_t ch){
	
	// ako je ADC kanal ve?i od 7, tada se u ADCSRB mora postaviti bit MUX5
	if (ch & ADC_MUX_MASK2){
		ADCSRB |= (1 << MUX5);
	}else{
		ADCSRB &= ~(1 << MUX5);
	}
	
	// ako se koristi on-chip temperaturni senzor, tada se mijenja referenca na 2.56V
	if (ch == ADCTEMP){
		ADMUX &= ~ADC_REFERENCE_MASK;
		ADMUX |= ADC_REFERENCE_256V;
	}
	
	ADMUX &= ~ADC_MUX_MASK1;
	ADMUX |= (ch & ADC_MUX_MASK1);
	
	ADCSRA |= (1<<ADSC);

	//Wait for conversion to complete
	while(!(ADCSRA & (1 << ADIF)));

	//Clear ADIF by writing one to it

	ADCSRA |= (1<<ADIF);
	
	// ako se koristi on-chip temperaturni senzor, tada se mijenja referenca na 2.56V
	// nakon izra?una ADC vrijednosti, referenca se vra?a na ADC_REFERENCE u adc.h
	if (ch == ADCTEMP){
		ADMUX &= ~ADC_REFERENCE_MASK;
		ADMUX |= ADC_REFERENCE;
	}
	
	return (ADC);  // read ADC (full 10 bits);
}