/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 11.1.1
 */ 

#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
#include "LCD/lcd.h"
#include "Interrupt/interrupt.h"

int brojac_int0 = 0;
int brojac_int1 = 0;
bool lcd_update = true;

// prekidna rutina za vanjski prekid INT0
ISR(INT0_vect) {
	brojac_int0++;
	lcd_update = true;
}

// prekidna rutina za vanjski prekid INT1
ISR(INT1_vect) {
	brojac_int1++;
	lcd_update = true;
	if(get_pin(PIND, PD1)) {
		toggle_port(PORTB, PB4);
	}
}

void inicijalizacija() {

	lcd_init(); // konfiguriranje LCD displeja
	
	//prvi nacin 	
	// konfiguracija prekida INT0
	EIMSK |= (1 << INT0);  // omoguci prekid INT0
	// padajuci brid generira prekid na INT0
	EICRA &= ~((1 << ISC01) | (1 << ISC00));
	EICRA |= (1 << ISC01) | (0 << ISC00); 
	
	// konfiguracija prekida INT1 
	
	interrupt_enable(); //omoguci globalni prekid
	// konfiguriranje ulaza PD0 i PD1 te izlaza PB4
	DDRD &= ~((1 << PD0) | (1 << PD1));
	PORTD |= (1 << PD0) | (1 << PD1);
	DDRB |= (1 << PB4);
}

int main(void) {
	
	inicijalizacija();

	while(1) {
		
		if(lcd_update) {				
			lcd_clrscr();
			lcd_home();
			lcd_print("INT0: %d\nINT1: %d", brojac_int0, brojac_int1);
			lcd_update = false;
		} 
			asm("nop"); // instrukcija koja kasni jedan ciklus CPU-a
	}
	return 0;
}