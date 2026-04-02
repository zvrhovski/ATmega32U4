/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 4.1.5
 */  

#include "AVR VUB/avrvub.h"
#include <avr/io.h>
#include <util/delay.h>


void inicijalizacija() {
	
	output_port(DDRB,PB7); // PB4 postavljen kao izlazni pin	
	output_port(DDRB,PB6); // PB6 postavljen kao izlazni pin
	output_port(DDRB,PB5); // PB5 postavljen kao izlazni pin
	output_port(DDRB,PB4); // PB4 postavljen kao izlazni pin
	set_port(PORTB,PB4,1); // postavljanje pina PB4 u visoko stanje
	
}

int main(void) {
	
	inicijalizacija(); // inicijalizacija mikrokontrolera
	
	while (1) { // beskonaèna petlja 
	
		for (int i = 4; i <= 7; i++) {
			
			_delay_ms(100);
			
			PORTB &= ~(1 << i);
			
			if (i != 7) {
				PORTB |= (1 << (i+1));
			}
			else {
				PORTB |= (1 << PB4);
			}
		}
	}
	return 0;
}