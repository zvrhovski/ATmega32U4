/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikroupravljaca AVR familije
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
	
	inicijalizacija(); // inicijalizacija mikroupravljaca
	
	while (1) { // beskonacna petlja 

	}
	return 0;
}