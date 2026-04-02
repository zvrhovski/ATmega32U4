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
	DigitalInput tipkalo2(D1); // stvori objekt tipkalo2 za tipkalo na pinu PD1
	DigitalInput tipkalo3(F6); // stvori objekt tipkalo3 za tipkalo na pinu PF6
	DigitalInput tipkalo4(F7); // stvori objekt tipkalo4 za tipkalo na pinu PF7
	
	tipkalo1.pullup_on(); //ukljuci pull up za pin PD0
	tipkalo2.pullup_on(); //ukljuci pull up za pin PD1	
	tipkalo3.pullup_on(); //ukljuci pull up za pin PF6	 
	tipkalo4.pullup_on(); //ukljuci pull up za pin PF7	
	
    while (1) {
		
		if (tipkalo1.state() == false) {
			crvena.on();
		} 
		else {
			crvena.off();
		}

		if (tipkalo2.filtered_state(false, 25) == false) {
			zuta.on();
		}
		else {
			zuta.off();
		}

		if (tipkalo3.isFalling_edge()){
			zelena.toggle();
		}

		if (tipkalo4.isRising_edge()){
			plava.toggle();
		}
    }
	return 0;
}

