/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 4.1.1
 */ 

#include "AVR VUB/avrvub.h"
#include <avr/io.h>

void inicijalizacija() {
	
	DDRB |= (1 << PB7); // pin PB7 izlazni pin
	PORTB |= (1 << PB7); // pin PB7 po?etno u visokom stanju
}


int main(void) {
		
	inicijalizacija();		
	
return 0;
	
}