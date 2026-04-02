/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 4.2.5
 */ 

#include "AVR VUB/avrvub.h"
#include <avr/io.h>

void inicijalizacija() {
	
	// PB7,PB6,PB5,i PB4 postavljeni kao izlazni pinovi
	DDRB |= (1 << PB7) | (1 << PB6) | (1 << PB5) | (1 << PB4);
	// PD1 i PD0 postavljeni kao izlazni pinovi
	DDRD &= ~((1 << PD1) | (1 << PD0));
	// PF7 i PF6 postavljeni kao izlazni pinovi
	DDRF &= ~((1 << PF7) | (1 << PF6));
	// pritezni otpornici ukljuceni na pinovima PD1 i PD0
	PORTD |= (1 << PD1) | (1 << PD0);
	// pritezni otpornici ukljuceni na pinovima PF7 i PF6
	PORTF |= (1 << PF7) | (1 << PF6);
}

int main(void) {
	
	inicijalizacija(); // inicijalizacija mikroupravljaca
	
	while (1) {
		// ako je padajuci brid na pinu PD0
		if(isFalling_edge(PD, PD0) == true) {	
			toggle_port(PORTB, PB4);	// promijeni stanje crvene LED diode
		}

		// ako je rastuci brid na pinu PD1	
		if(isRising_edge(PD,PD1) == true) {	
			toggle_port(PORTB, PB5);	// promijeni stanje zute LED diode
		}
			
		// ako je padajuci brid na pinu PF6
		if(isFalling_edge(PF,PF6) == true) {	
			toggle_port(PORTB, PB6);	// promijeni stanje zelene LED diode
		}
		
		// ako je rastuci brid na pinu PF7	
		if(isRising_edge(PF,PF7) == true) {	
			toggle_port(PORTB, PB7);	// promijeni stanje plave LED diode
		}
	}
	return 0;
}