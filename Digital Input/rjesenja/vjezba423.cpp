/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 4.2.3
 */ 

#include "AVR VUB/avrvub.h"
#include <avr/io.h>

void inicijalizacija() {
	
	output_port(DDRB,PB7); // PB7 postavljen kao izlazni pin
	output_port(DDRB,PB6); // PB6 postavljen kao izlazni pin
	output_port(DDRB,PB5); // PB5 postavljen kao izlazni pin
	output_port(DDRB,PB4); // PB4 postavljen kao izlazni pin

	input_port(DDRD,PD0); // PD0 postavljen kao ulazni pin
	input_port(DDRD,PD1); // PD1 postavljen kao ulazni pin
	input_port(DDRF,PF6); // PF6 postavljen kao ulazni pin
	input_port(DDRF,PF7); // PF7 postavljen kao ulazni pin
	
	set_port(PORTD,PD0,1); // ukljucivanje priteznog otpornika na PD0
	set_port(PORTD,PD1,1); // ukljucivanje priteznog otpornika na PD1
	set_port(PORTF,PF6,1); // ukljucivanje priteznog otpornika na PF6
	set_port(PORTF,PF7,1); // ukljucivanje priteznog otpornika na PF7
}

int main(void) {
	
	inicijalizacija(); // inicijalizacija mikroupravljaca
	
	while (1) {

		if(get_pin(PIND,PD0) == 0) {	// ako je pin PD0 u logickoj nuli
			set_port(PORTB, PB4, 1);	// ukljuci crvenu LED diodu
		}
		else {
			set_port(PORTB, PB4, 0);	// inace je iskljuci
		}
			
		if(get_pin(PIND,PD1) == 0) {	// ako je pin PD1 u logickoj nuli
			set_port(PORTB, PB5, 1);	// ukljuci zutu LED diodu
		}
		else {
			set_port(PORTB, PB5, 0);	// inace je iskljuci
		}		
		
		if(get_pin(PINF,PF6) == 0) {	// ako je pin PF6 u logickoj nuli
			set_port(PORTB, PB6, 1);	// ukljuci ?zelenu LED diodu
		}
		else {
			set_port(PORTB, PB6, 0);	// inace je iskljuci
		}

		if(get_pin(PINF,PF7) == 0) {	// ako je pin PF7 u logickoj nuli
			set_port(PORTB, PB7, 1);	// ukljuci plavu LED diodu
		}
		else {
			set_port(PORTB, PB7, 0);	// inace je iskljuci
		}	
	}
	return 0;
}