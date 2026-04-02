/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 8.1.1
 */ 

#include "AVR VUB/avrvub.h"
#include "LCD/lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include "Timer/timer.h"
#include "Interrupt/interrupt.h"

// prekidna rutina za timer0
ISR(TIMER0_OVF_vect) { 
	TCNT0 = 0; // pocetna vrijednost registra
	toggle_port(PORTB, PB4);
}

void inicijalizacija() {
	
	DDRB |= (1 << PB4);  // PB4 izlazni pin	
	// inicijalizacija za timer0 - prvi nacin
	timer0_set_normal_mode();
	timer0_set_prescaler(TIMER0_PRESCALER_1024);
	timer0_interrupt_OVF_enable();
	
	lcd_init(); // inicijalizacija lcd displeja
	//interrupt_enable(); // globalno omoguci prekide //sei();
	TCNT0 = 0; // pocetna vrijednost registra
}

int main(void) {
		
	inicijalizacija();
	uint16_t minute = 0;
		
	while(1) {
	
		lcd_clrscr();
		lcd_home();
		lcd_print("ON : %u min", minute++);
		_delay_ms(60000); // ka?snjenje 60 s
	}
	return 0;
}