/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 9.1.4
 */ 
#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
#include "DigitalIO/DigitalIO.h"
#include "SSD i SBR/ssd_sbr.h"
#include "ADC/adc.h"

void inicijalizacija(){
	adc_init(); // inicijalizacija AD pretvorbe
}

int main(void) {
	
	inicijalizacija();
	// stvaranje objekta za posmacni registar
	Shift_Bit_Register SBR(C7, F1, F0);
	
	uint8_t d1, d2, d3, d4;	
	uint16_t napon_mV; 
	
	while(1) {
		
		napon_mV = adc_read(ADC5) * 5000.0 / 1023.0;
		// racunanje znamenaka za prikaz
		d1 = napon_mV / 1000;
		d2 = (napon_mV / 100) % 10;
		d3 = (napon_mV / 10) % 10;
		d4 = napon_mV % 10;
		// slanje cetiri bajta na posmacne registre
		SBR.send_4byte(digits[d1] | DOT, digits[d2], digits[d3], digits[d4]);
		_delay_ms(200);
	}
	return 0;
}