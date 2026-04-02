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
	
	lcd_init(); // inicijalizacija lcd displeja
	adc_init(); // inicijalizacija AD pretvorbe
}

int main(void) {
	
	inicijalizacija();

	uint16_t ADC_4; // vrijednost AD pretvorbe na pinu ADC4
	float T; // temperatura
	
	while(1) {
		
		ADC_4 = adc_read(ADC4);
		
		// dodajte relaciju za temperaturu NTC otpornika 

		lcd_clrscr();
		lcd_home();
		lcd_print("T = %0.2f%cC\n", T, 223);
		
		// signalizacija po istom principu kao u daatoteci vjezba713.c
	
		_delay_ms(1000);
	}
	return 0;
}