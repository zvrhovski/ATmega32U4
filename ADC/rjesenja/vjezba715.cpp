/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 7.1.5
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

	uint16_t ADC_4; // vrijednost AD pretvorbe na pinu ADC4
	float T; // temperatura
	
	while(1) {
		
		ADC_4 = adc_read(ADC4);
		T = 3435 / (log(ADC_4/(1023.0 - ADC_4))+10.861) - 273.15;

		lcd_clrscr();
		lcd_home();
		lcd_print("T = %0.2f%cC\n", T, 223);
		
		// signalizacija po istom principu kao u daatoteci vjezba713.c
		if(T < 25.0) { 
				
			set_port(PORTB,PB4,1);
			set_port(PORTB,PB5,0);
			set_port(PORTB,PB6,0);
			set_port(PORTB,PB7,0);
		}
			
		if(T >= 25.0 && T < 27.5) {
				
			set_port(PORTB,PB4,1);
			set_port(PORTB,PB5,1);
			set_port(PORTB,PB6,0);
			set_port(PORTB,PB7,0);
		}

		if(T >= 27.5 && T < 30.0) {
				
			set_port(PORTB,PB4,1);
			set_port(PORTB,PB5,1);
			set_port(PORTB,PB6,1);
			set_port(PORTB,PB7,0);
		}
			
		if(T >= 30.0) {
				
			set_port(PORTB,PB4,1);
			set_port(PORTB,PB5,1);
			set_port(PORTB,PB6,1);
			set_port(PORTB,PB7,1);
		}
		
		_delay_ms(1000);
	}
	return 0;
}