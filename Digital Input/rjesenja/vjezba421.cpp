/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 4.2.1
 */ 


#include "AVR VUB/avrvub.h"
#include <avr/io.h>

void inicijalizacija() {
	/*
	output_port(DDRB,PB7); // PB7 postavljen kao izlazni pin
	output_port(DDRB,PB6); // PB6 postavljen kao izlazni pin
	output_port(DDRB,PB5); // PB5 postavljen kao izlazni pin
	output_port(DDRB,PB4); // PB4 postavljen kao izlazni pin

	input_port(DDRD,PD0); // PD0 postavljen kao ulazni pin
	set_port(PORTD,PD0,1); // ukljucenje priteznog otpornika na PD0
	*/
	DDRB |= (1 << PB7) | (1 << PB6) | (1 << PB5) | (1 << PB4);
	DDRD &= ~(1 << PD0);
	
	PORTD |= (1 << PD0);
}

int main(void){
	
	inicijalizacija(); // inicijalizacija mikrokontrolera
	
	while (1) {
		if((PIND & 0x01) == 0x00) { // ako je pin PD0 u logickoj nuli
			PORTB |= 0xF0;       // ukljuci sve led diode
		}
		else {
			PORTB &= ~0xF0;	   // inace ih iskljuci
		}
	}
	return 0;
}