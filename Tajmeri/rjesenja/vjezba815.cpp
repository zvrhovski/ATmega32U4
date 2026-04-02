/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 8.1.5
 */ 

#include "AVR VUB/avrvub.h"
#include "LCD/lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include "Timer/timer.h"
#include "Interrupt/interrupt.h"

uint8_t brojac = 0;

// prekidna rutina za timer1
ISR(TIMER1_OVF_vect) { 
	TCNT1 = 3036; // pocetna vrijednost registra
	switch (++brojac) {
		case 1:
			set_port(PORTB,PB4,1);
			set_port(PORTB,PB7,0);
		break;
		case 2:
			set_port(PORTB,PB5,1);
			set_port(PORTB,PB4,0);
		break;
		case 3:
			set_port(PORTB,PB6,1);
			set_port(PORTB,PB5,0);
		break;
		case 4:
			set_port(PORTB,PB7,1);
			set_port(PORTB,PB6,0);
			brojac = 0;
		break;
		default:
		break;
	}
}

void inicijalizacija() {
	// PB4, PB5, PB6, PB7 izlazni pinovi
	DDRB |= (1 << PB4) | (1 << PB5) | (1 << PB6) | (1 << PB7); 
	// inicijalizacija za timer1 - prvi nacin
	timer1_set_normal_mode();
	timer1_set_prescaler(TIMER1_PRESCALER_64);
	timer1_interrupt_OVF_enable();

	lcd_init(); // inicijalizacija lcd displeja
	interrupt_enable(); // globalno omoguci prekide //sei();
	TCNT1 = 3036; // pocetna vrijednost registra
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