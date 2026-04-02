/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 9.1.1 - treci nacin
 */ 

#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
#include "DigitalIO/DigitalIO.h"

int main(void) {
	// stvaranje objekta za posmacni registar
	Shift_Bit_Register SBR(C7, F1, F0);
	
	uint8_t number = 0x66;
	// petlja koja pojedinacno salje cetiri bajta
	for(int n = 0; n < 4; n++) {
		SBR.send_1byte(number);
	}
	// generiranje impulsa na RCK 
	SBR.clock_rck();
	
	while(1) {
		
		_delay_ms(100);
	}
	return 0;
}
