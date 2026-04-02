/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 4.1.2
 */  

#include "AVR VUB/avrvub.h"
#include <avr/io.h>
#include <util/delay.h>

void inicijalizacija() {
	
	DDRB |= (1 << PB7); // pin PB7 izlazni pin
	PORTB |= (1 << PB7); // pin PB7 po?etno u visokom stanju
}

int main(void) {
	
	inicijalizacija();
	
	_delay_ms(1000); // funkcija kasnjenja koja kao argument prima vrijeme u ms
	
	set_port(PORTB,PB7,0); // postavljanje PB7 u logicku nulu
	
	_delay_us(1000000); // funkcija ka?snjenja koja kao argument prima vrijeme u us
	
	set_port(PORTB,PB7,1);
	
	_delay_ms(1000);
	
	PORTB &= 0x7F; // postavljanje PB7 u logicku nulu
	
	_delay_us(1000000);
	
	set_port(PORTB,PB7,1);
	
	_delay_ms(1000);
	
	PORTB &= ~(1 << PB7); // postavljanje PB7 u logicku nulu

	// za?sto led dioda ne izmijenjuje stanja nakon ove linije koda?
	// ?sto napraviti ????
	return 0;
	
}