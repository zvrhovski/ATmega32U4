/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 4.2.6
 */  
#include "AVR VUB/avrvub.h"
#include "DigitalIO/DigitalIO.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	
	// instance objekata digitalnih izlaza
	DigitalOutput plava(B7); // stvori objekt plava za diodu na pinu PB7
	DigitalOutput zelena(B6); // stvori objekt zelena za diodu na pinu PB6
	DigitalOutput zuta(B5); // stvori objekt zuta za diodu na pinu PB5
	DigitalOutput crvena(B4); // stvori objekt crvena za diodu na pinu PB4

	// instance objekata digitalnih ulaza
	DigitalInput tipkalo1(D0); // stvori objekt tipkalo1 za tipkalo na pinu PD0
	// instancirati ostale digitalne ulaze
	
	tipkalo1.pullup_on(); //ukljuci pull up za pin PD0
	//ukljuciti ostale pull up otpornike
	
	while (1) {
		
		// napraviti funkcionalnost zadanu zadatkom
    }
	return 0;
}

