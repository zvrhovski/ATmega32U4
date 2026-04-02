/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 4.2.4
 */ 

#include "AVR VUB/avrvub.h"
#include <avr/io.h>

void inicijalizacija() {
	
	// PB7,PB6,PB5,i PB4 postavljeni kao izlazni pinovi
	DDRB |= (1 << PB7) | (1 << PB6) | (1 << PB5) | (1 << PB4);
	// PD1 i PD0 postavljeni kao ulazni pinovi
	DDRD &= ~((1 << PD1) | (1 << PD0));
	// PF7 i PF6 postavljeni kao ulazni pinovi
	DDRF &= ~((1 << PF7) | (1 << PF6));
	// pritezni otpornici ukljuceni na pinovima PD1 i PD0
	PORTD |= (1 << PD1) | (1 << PD0);
	// pritezni otpornici ukljuceni na pinovima PF7 i PF6
	PORTF |= (1 << PF7) | (1 << PF6);
}

int main(void) {
	
	inicijalizacija(); // inicijalizacija mikroupravljaca
	
	
	while (1) {
		// ako je filtrirani pin PD0 u logickoj nuli
		if(filtered_pin_state(PD,PD0,false,30) == false) {	
			set_port(PORTB, PB4, 1);	// ukljuci crvenu LED diodu
		}
		else {
			set_port(PORTB, PB4, 0);	// inace je iskljuci
		}
		// nastavite za ostala tipkala	
	}
	return 0;
}