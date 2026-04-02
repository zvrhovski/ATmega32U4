/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 4.1.8
 */  
#include "AVR VUB/avrvub.h"
#include "DigitalIO/DigitalIO.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void) {

	DigitalOutput plava(B7); // stvori objekt plava za diodu na pinu PB7
	DigitalOutput zelena(B6); // stvori objekt zelena za diodu na pinu PB6
	DigitalOutput zuta(B5); // stvori objekt zuta za diodu na pinu PB5
	DigitalOutput crvena(PB, PB4); // stvori objekt crvena za diodu na pinu PB4

    while (1) {

		plava.toggle(); // promjena stanja plave diode
		_delay_ms(250); // cekaj 250 ms
		plava.toggle(); // promjena stanja plave diode
		zelena.on(); // ukljuci zelenu diodu
		_delay_ms(250); // cekaj 250 ms
		zelena.off(); // iskljuci zelenu diodu
		zuta.set(); // ukljuci zutu diodu
		_delay_ms(250); // cekaj 250 ms
		zuta.reset(); // iskljuci zutu diodu
		crvena.on(); // ukljuci crvenu diodu
		_delay_ms(250); // cekaj 250 ms
		crvena.off(); // iskljuci crvenu diodu
    }
}

