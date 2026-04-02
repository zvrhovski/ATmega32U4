/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikroupravljaca AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 4.1.8
 */  
#include "AVR VUB/avrvub.h"
#include "DigitalIO/DigitalIO.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void) {

	DigitalOutput plava(B7); // stvori objekt plava za diodu na pinu PB7

    while (1) {

		plava.toggle(); // promjena stanja plave diode
		_delay_ms(250); // cekaj 250 ms

    }
	return 0;
}

