/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 4.1.3
 */  


#include "AVR VUB/avrvub.h"
#include <avr/io.h>
#include <util/delay.h>

void inicijalizacija() {
	
	DDRB |= (1 << PB7); // pin PB7 izlazni pin
	PORTB |= (1 << PB7); // pin PB7 po?etno u visokom stanju
}
		
int main(void) {
		
	inicijalizacija(); // inicijalizacija mikrokontrolera
	
	while (1) { // beskonaèna petlja u kojoj mikrokontroler ostaje dok god ima napajanja te dok nije u RESET-u
			
		_delay_ms(1000); // funkcija ka?njenja koja kao argument prima vrijeme u ms
		
		toggle_port(PORTB,PB7); // promijeni stanje PB7
		
	}
return 0;	
}