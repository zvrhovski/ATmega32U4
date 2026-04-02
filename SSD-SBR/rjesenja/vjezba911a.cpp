/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 9.1.1 - drugi nacin
 */ 

#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
#include "DigitalIO/DigitalIO.h"

int main(void) {
	
	DigitalOutput ShiftReg_SI(C7);
	DigitalOutput ShiftReg_SCK(F1);
	DigitalOutput ShiftReg_RCK(F0);
	
	uint8_t number;
	
	for(int n = 0; n < 4; n++) {
		number = 0x66;
		for(int i = 0; i < 8; i++) {
			if(number & 0x01) { // ako je bit0 == 1
				ShiftReg_SI.set(); // na SI posalji 1
			}
			else { // ako je bit0 == 0
				ShiftReg_SI.reset(); // na SI posalji 0
			}
			// rastuci brid signala SCK
			ShiftReg_SCK.set(); //SCK = 1
			_delay_us(1);
			ShiftReg_SCK.reset(); //SCK = 0
			_delay_us(1);
		
			number = number >> 1; // posmakni broj za jedan u desno
		}
	}
	// rastuci brid signala RCK
	ShiftReg_RCK.set(); //RCK = 1
	_delay_us(1);
	ShiftReg_RCK.reset(); //RCK = 0
	_delay_us(1);
	
	while(1) {
		
	_delay_ms(100);
	}
	return 0;
}