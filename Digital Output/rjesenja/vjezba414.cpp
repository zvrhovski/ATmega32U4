/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 4.1.4
 */  

#include "AVR VUB/avrvub.h"
#include <avr/io.h>
#include <util/delay.h>


void inicijalizacija() {
	
	DDRB |= (1 << PB7) | (1 << PB6) | (1 << PB5) | (1 << PB4); // PB7, PB6, PB5 i PB4 izlazni pinovi
	PORTB |= (1 << PB4); // postavljanje PB4 u visoko stanje
}

int main(void) {
	
	inicijalizacija(); // inicijalizacija mikrokontrolera
	
	while (1) { // beskonaèna petlja 
		_delay_ms(100); // ka?njenje 100 ms
		
		toggle_port(PORTB,PB4); // Promijeni stanje pina PB4
		
		toggle_port(PORTB,PB5); // Promijeni stanje pina PB5
		
		_delay_ms(100); // ka?njenje 100 ms
		
		toggle_port(PORTB,PB5); // Promijeni stanje pina PB5
		
		toggle_port(PORTB,PB6); // Promijeni stanje pina PB6

		_delay_ms(100); // ka?njenje 100 ms
		
		toggle_port(PORTB,PB6); // Promijeni stanje pina PB6
		
		toggle_port(PORTB,PB7); // Promijeni stanje pina PB7

		_delay_ms(100); // ka?njenje 100 ms
		
		toggle_port(PORTB,PB7); // Promijeni stanje pina PB7
		
		toggle_port(PORTB,PB4); // Promijeni stanje pina PB4	
	}
	return 0;
}