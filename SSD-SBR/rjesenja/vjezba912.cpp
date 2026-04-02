/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 9.1.2
 */ 

#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
#include "DigitalIO/DigitalIO.h"

//#include "SSD i SBR/ssd_sbr.h" // otkomentiraj za drugi nacin

int main(void) {
	
	//shift_bit_init(); // otkomentiraj za drugi nacin
	
	// stvaranje objekta za posmacni registar
	Shift_Bit_Register SBR(C7, F1, F0);
	
	// heksadecimalni kodovi znakova sa slika 9.10 i 9.11
	uint8_t signs1[4] = {0x9C, 0x6E, 0x0C, 0xCE};
	uint8_t signs2[4] = {0xF2, 0xDA, 0x7C, 0x66};
			
	while(1) {
		// posalji znakove sa slike 9.10
		for(int n = 0; n < 4; n++) {
			SBR.send_1byte(signs1[n]);
			//shift_bit_send_1byte(signs1[n]); // otkomentiraj za drugi nacin
		}	
		SBR.clock_rck(); // generiranje impulsa na RCK 
		//shift_bit_clock_rck(); // otkomentiraj za drugi nacin
		_delay_ms(1000);
		
		// posalji znakove sa slike 9.11
		SBR.send_4byte(signs2[0], signs2[1], signs2[2], signs2[3]);
		//shift_bit_send_4byte(signs2[0], signs2[1], signs2[2], signs2[3]);// otkomentiraj za drugi nacin
		_delay_ms(1000);
	}
	return 0;
}

