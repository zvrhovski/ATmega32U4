/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 4.1.6
 */  

#include "AVR VUB/avrvub.h"
#include <avr/io.h>
#include <util/delay.h>

void inicijalizacija() {
	
	DDRB |= (1 << PB7) | (1 << PB6) | (1 << PB5) | (1 << PB4); // PB7, PB6, PB5 i PB4 izlazni pinovi
	PORTB |= (1 << PB4); // postavljanje PB7 u visoko stanje
	
	DDRF |= (1 << PF4); //pin PF4 za Buzzer 
}

int main(void) {
	
	inicijalizacija(); // inicijalizacija mikrokontrolera
	
	for (int i = 0; i < 50; i++) { // petlja koja se izvodi 50 puta

		_delay_ms(100); // kasnjenje 100 ms
	
		toggle_port(PORTB,PB4); // Promijeni stanje pina PB4
	
		toggle_port(PORTB,PB5); // Promijeni stanje pina PB5
	
		_delay_ms(100); // kasnjenje 100 ms
	
		toggle_port(PORTB,PB5); // Promijeni stanje pina PB5
	
		toggle_port(PORTB,PB6); // Promijeni stanje pina PB6

		_delay_ms(100); // kasnjenje 100 ms
	
		toggle_port(PORTB,PB6); // Promijeni stanje pina PB6
	
		toggle_port(PORTB,PB7); // Promijeni stanje pina PB7

		_delay_ms(100); // kasnjenje 100 ms
	
		toggle_port(PORTB,PB7); // Promijeni stanje pina PB7
	
		toggle_port(PORTB,PB4); // Promijeni stanje pina PB4
	}
	
	// ovdje ugasiti crvenu LED diodu
	toggle_port(PORTB,PB4); // Promijeni stanje pina PB4
	// ovdje ukljuciti Buzzer
	set_port(PORTF,PF4, 1);

	return 0;	
}