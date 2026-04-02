/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 4.2.5
 */ 

#include "AVR VUB/avrvub.h"
#include <avr/io.h>

void inicijalizacija() {
	
	//napravite konfiguraciju
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
		// nastavite za ostala tipkala			
	}
	return 0;
}