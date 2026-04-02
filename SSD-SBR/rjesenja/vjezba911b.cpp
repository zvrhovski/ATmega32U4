/*
 * vjezba911b.cpp
 *
 * Created: 14.4.2020. 23:51:56
 *  Author: Zoran
 */ 


#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
#include "SSD i SBR/ssd_sbr.h"

void inicijalizacija() {
	// konfiguracija pinova mikroupravljaca koji su spojeni 
	// na Shift Bit Register (definirati konstante u ssd_sbr.h)
	shift_bit_init(); 
}

int main(void) {
	
	inicijalizacija();

	uint8_t number = 0x66;
	
	// petlja koja pojedinacno salje cetiri bajta
	for(int n = 0; n < 4; n++) {
		shift_bit_send_1byte(number); 
	}
	// generiranje impulsa na RCK 
	shift_bit_clock_rck();
	
	while(1) {
		
		_delay_ms(100);
	}
	return 0;
}