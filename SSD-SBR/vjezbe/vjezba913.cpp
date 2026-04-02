/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 9.1.3
 */ 

#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
#include "DigitalIO/DigitalIO.h"
#include "SSD i SBR/ssd_sbr.h"

int main(void) {
	// stvaranje objekta za posmacni registar
	Shift_Bit_Register SBR(C7, F1, F0);
	DigitalInput StartStop(D0); // PD0 ulazni pin
	DigitalInput Clear(D1); // PD1 ulazni pin
	
	StartStop.pullup_on(); //pull up na PD0
	Clear.pullup_on(); //pull up na PD1
	
	uint16_t desetinke = 0;
	uint8_t d1 = 0, d2 = 0, d3 = 0, d4 = 0;
	// slanje cetiri bajta na posmacne registre
	SBR.send_4byte(digits[d1], digits[d2], digits[d3] | DOT, digits[d4]);
		
	bool counting = false;
	bool count_up = true;
			
	while(1) {
		// na padajuci brid tipkala StartStop
		if(StartStop.isFalling_edge()) {
			if (counting)	{
				counting = false;
			}
			else {
				counting = true;
			}
		} 
		// na padajuci brid tipkala Clear
		if(Clear.isFalling_edge()) {
			desetinke = 0;
			d1 = d2 = d3 = d4 = 0;
			SBR.send_4byte(digits[d1], digits[d2], digits[d3] | DOT, digits[d4]);
		}
						
		if (counting)	{
			// racunanje znamenaka 
			d1 = desetinke / 1000;
			d2 = (desetinke / 100) % 10;
			d3 = (desetinke / 10) % 10;
			d4 = desetinke % 10;
			
			SBR.send_4byte(digits[d1], digits[d2], digits[d3] | DOT, digits[d4]);
			
			// brojanje desetinki sekunde
			_delay_ms(100);
			if (++desetinke > 9999) {
				desetinke = 0;
			}
		}
	}
	return 0;
}

