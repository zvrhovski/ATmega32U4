/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 12.2.1
 */ 

#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
#include "DigitalIO/DigitalIO.h"

int main(void) {
	// objekti za relej i tipkalo
	DigitalOutput Relej(D4);
	DigitalInput Tipkalo1(D0);
	Tipkalo1.pullup_on();
	// pomocne varijable kojima se prati vrijeme pritisnutog tipkala
	uint16_t time_on = 0;
	bool time_is_up = false;

	while(1) {
		// ako je tipkalo pritisnuto i vrijeme od 5s nije isteklo		
		if(Tipkalo1.state() == false && !time_is_up) {
			time_on++; 
		}
		// kada se otpusti tipkalo
		if(Tipkalo1.isRising_edge()) {
			time_is_up = false;
		}
		// ako je vrijeme vece od 5s i relej je bio iskljucen		
		if((time_on > 500) && (Relej.state() == false)) {
			Relej.on();
			time_is_up = true;
			time_on	= 0;
		}
		// ako je vrijeme vece od 5s i relej je bio ukljucen
		if((time_on > 500) && (Relej.state() == true)) {
			Relej.off();
			time_is_up = true;
			time_on	= 0;
		}	
		_delay_ms(10);
	}
	return 0;
}