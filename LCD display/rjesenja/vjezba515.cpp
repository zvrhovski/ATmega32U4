/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 5.1.5
 */ 

#include "AVR VUB/avrvub.h"
#include "LCD/lcd.h"
#include <avr/io.h>
#include <util/delay.h>

void inicijalizacija() {
	
	output_port(DDRB,PB7); //pin PB7 postavljen kao izlaz
	input_port(DDRD,PD0);  //pin PD0 postavljen kao ulaz
	set_port(PORTD,PD0,1); // ukljucen pritezni otpornik na PD0
	
	lcd_init(); // inicijalizacija lcd displeja
}

int main(void) {
	
	inicijalizacija();

	uint8_t sec = 0;
	uint8_t min = 0;
	uint16_t sat = 0;
	
	while (1) {
		
		lcd_clrscr();
		lcd_home();
		lcd_print("%dh:%dm:%ds", sat,min,sec);
		
		_delay_ms(1000);
		
		toggle_port(PORTB,PB7);
		
		if(++sec >= 60) {
			sec = 0;
			min++;
		}
		
		if(min >= 60) {
			min = 0;
			sat++;
		}
		
		if(get_pin(PIND,PD0) == 0) {
			sec = 0;
			min = 0;
			sat = 0;
			set_port(PORTB,PB7,0);
		}
	}
	return 0;
}