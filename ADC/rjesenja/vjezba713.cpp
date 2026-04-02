/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 7.1.3
 */ 

#include "AVR VUB/avrvub.h"
#include "LCD/lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include "ADC/adc.h"

void inicijalizacija() {
	
	//pinovi PB7, PB6, PB5 i PB4 postavljeni kao izlazni
	DDRB |= (1 << PB7) | (1 << PB6) | (1 << PB5) | (1 << PB4);
	
	lcd_init(); // inicijalizacija lcd displeja
	adc_init(); // inicijalizacija AD pretvorbe
}

int main(void) {
	
	inicijalizacija();

	uint16_t ADC_5; // vrijednost AD pretvorbe na pinu ADC5
	float U_ADC5; // napon na pinu ADC5
	const float V_REF = 5.0; // AVCC je referentni napon
	float y[2] = {0, 0}; // {y[k-1], y[k]}
	uint8_t k = 1;
	
	while(1) {
		
		ADC_5 = adc_read(ADC5);
		
		y[k] = 0.2 * y[k - 1] + 0.8 * ADC_5;
		
		U_ADC5 = y[k] * V_REF / 1023.0;
		
		lcd_clrscr();
		lcd_home();
		lcd_print("ADC5 = %d", ADC_5);
		lcd_print("\nUADC5 = %.2fV", U_ADC5);
		
		_delay_ms(100);
		
		y[k-1] = y[k];

		if(U_ADC5 < 1.25) {	
			set_port(PORTB,PB4,1);
			set_port(PORTB,PB5,0);
			set_port(PORTB,PB6,0);
			set_port(PORTB,PB7,0);
		}
		
		if(U_ADC5 >= 1.25 && U_ADC5 < 2.5) {
			set_port(PORTB,PB4,1);
			set_port(PORTB,PB5,1);
			set_port(PORTB,PB6,0);
			set_port(PORTB,PB7,0);
		}

		if(U_ADC5 >= 2.5 && U_ADC5 < 3.75) {
			set_port(PORTB,PB4,1);
			set_port(PORTB,PB5,1);
			set_port(PORTB,PB6,1);
			set_port(PORTB,PB7,0);
		}
		
		if(U_ADC5 >= 3.75) {			
			set_port(PORTB,PB4,1);
			set_port(PORTB,PB5,1);
			set_port(PORTB,PB6,1);
			set_port(PORTB,PB7,1);
		}
	}
	return 0;
}