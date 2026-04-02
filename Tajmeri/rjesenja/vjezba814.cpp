/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 8.1.4
 */ 

#include "AVR VUB/avrvub.h"
#include "LCD/lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include "Timer/timer.h"
#include "Interrupt/interrupt.h"

uint8_t prazan_hod_timer0 = 0;

// prekidna rutina za timer0
ISR(TIMER0_OVF_vect) {
	TCNT0 = 22; // pocetna vrijednost registra
	if(++prazan_hod_timer0 == 20) {
	toggle_port(PORTB, PB4);
	prazan_hod_timer0 = 0;
	}
}

// prekidna rutina za timer1
ISR(TIMER1_OVF_vect) {
	TCNT1 = 46786; // pocetna vrijednost registra
	toggle_port(PORTB, PB5);
}

// prekidna rutina za timer3
ISR(TIMER3_OVF_vect) { 
	TCNT3 = 46786; // pocetna vrijednost registra
	toggle_port(PORTB, PB6);
}

void inicijalizacija() {
	DDRB |= (1 << PB4) | (1 << PB5) | (1 << PB6); // PB4, PB5 i PB6 izlazni pinovi

	// inicijalizacija za timer0
	timer0_set_normal_mode();
	timer0_set_prescaler(TIMER0_PRESCALER_1024);
	timer0_interrupt_OVF_enable();

	// inicijalizacija za timer1
	timer1_set_normal_mode();
	timer1_set_prescaler(TIMER1_PRESCALER_256);
	timer1_interrupt_OVF_enable();
	
	// inicijalizacija za timer3
	timer3_set_normal_mode();
	timer3_set_prescaler(TIMER3_PRESCALER_256);
	timer3_interrupt_OVF_enable();
		
	lcd_init(); // inicijalizacija lcd displeja
	interrupt_enable(); // globalno omoguci prekide //sei();
	
	TCNT0 = 22; // pocetna vrijednost registra za timer0
	TCNT1 = 46786; // pocetna vrijednost registra za timer1
	TCNT3 = 46786; // pocetna vrijednost registra za timer3
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