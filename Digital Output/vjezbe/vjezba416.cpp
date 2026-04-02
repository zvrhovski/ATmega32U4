/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikroupravljaca AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 4.1.6
 */  

#include "AVR VUB/avrvub.h"
#include <avr/io.h>

void inicijalizacija() {
	
	DDRB |= (1 << PB7) | (1 << PB6) | (1 << PB5) | (1 << PB4); // PB7, PB6, PB5 i PB4 izlazni pinovi
	PORTB |= (1 << PB4); // postavljanje PB7 u visoko stanje
	
	DDRF |= (1 << PF4); //pin PF4 za Buzzer 
}

int main(void) {
	
	inicijalizacija(); // inicijalizacija mikroupravljaca
	
	for (int i = 0; i < 50; i++) { // petlja koja se izvodi 50 puta
	}
	// ovdje ugasiti crvenu LED diodu

	// ovdje ukljuciti Buzzer
	
	return 0;	
}