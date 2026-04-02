/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 8.1.2
 */ 

#include "AVR VUB/avrvub.h"
#include "LCD/lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include "Timer/timer.h"
#include "Interrupt/interrupt.h"

// prekidna rutina za timer1
ISR(TIMER1_OVF_vect) { 
	TCNT1 = 0; // pocetna vrijednost registra
	toggle_port(PORTB, PB5);
}

void inicijalizacija() {
	DDRB |= (1 << PB5); // PB5 izlazni pin
	// inicijalizacija za timer1 - prvi nacin
	timer1_set_normal_mode();
	timer1_set_prescaler(TIMER1_PRESCALER_64);
	timer1_interrupt_OVF_enable();

	lcd_init(); // inicijalizacija lcd displeja
	interrupt_enable(); // globalno omoguci prekide //sei();
	TCNT1 = 0; // pocetna vrijednost registra
}

int main(void) {
		
	inicijalizacija();
	uint16_t minute = 0;
		
	while(1) {
	
		lcd_clrscr();
		lcd_home();
		lcd_print("ON : %u min", minute++);
		_delay_ms(60000); // kasnjenje 60 s
	}
	return 0;
}