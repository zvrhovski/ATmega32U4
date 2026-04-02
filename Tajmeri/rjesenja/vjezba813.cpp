/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 8.1.3
 */ 

#include "AVR VUB/avrvub.h"
#include "LCD/lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include "Timer/timer.h"
#include "Interrupt/interrupt.h"

// prekidna rutina za timer3
ISR(TIMER3_OVF_vect) { 
	TCNT3 = 3036; // pocetna vrijednost registra
	toggle_port(PORTB, PB6);
}

void inicijalizacija() {
	DDRB |= (1 << PB6); // PB6 izlazni pin
	// inicijalizacija za timer3
	timer3_set_normal_mode();
	timer3_set_prescaler(TIMER1_PRESCALER_256);
	timer3_interrupt_OVF_enable();
		
	lcd_init(); // inicijalizacija lcd displeja
	interrupt_enable(); // globalno omoguci prekide //sei();
	TCNT3 = 3036; // pocetna vrijednost registra
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