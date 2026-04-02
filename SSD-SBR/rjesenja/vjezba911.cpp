/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 9.1.1
 */ 

#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>

void inicijalizacija() {

	output_port(DDRC, PC7); // digitalni izlaz spojen na SI
	output_port(DDRF, PF1); // digitalni izlaz spojen na SCK
	output_port(DDRF, PF0); // digitalni izlaz spojen na RCK
}

int main(void) {
	
	inicijalizacija();

	uint8_t number;

	for(int n = 0; n < 4; n++) {
		number = 0x66;
		for(int i = 0; i < 8; i++) {
			if(number & 0x01) { // ako je number LSB == 1
				set_port(PORTC, PC7, 1); // na SI posalji 1
			}
			else { // ako je number LSB == 0
				set_port(PORTC, PC7, 0); // na SI posalji 0
			}
			// rastuci brid signala SCK
			set_port(PORTF, PF1, 1); //SCK = 1
			_delay_us(1);
			set_port(PORTF, PF1, 0); //SCK = 0
			_delay_us(1);
		
			number = number >> 1; // posmakni broj za jedan u desno
		}
	}
	
	// rastuci brid signala RCK
	set_port(PORTF, PF0, 1); //RCK = 1
	_delay_us(1);
	set_port(PORTF, PF0, 0); //RCK = 0
	_delay_us(1);
	
	while(1) {
		
	_delay_ms(100);
	}
	return 0;
}