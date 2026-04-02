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
	TCNT0 = 22; // pocetna vrijednost registra
	toggle_port(PORTB, PB4);
}

void inicijalizacija() {
	
	DDRB |= (1 << PB4);  // PB4 izlazni pin	
	// inicijalizacija za timer0 - prvi nacin
	timer0_set_normal_mode();
	timer0_set_prescaler(TIMER0_PRESCALER_1024);
	timer0_interrupt_OVF_enable();

	
/*	// inicijalizacija za timer0 - drugi nacin
	// postaviti normalna nacin rada za timer0
	TCCR0A |= (0 << WGM01) | (0 << WGM00);
	TCCR0B |= (0 << WGM02);
	//postaviti djelitelj frekvencije na 1024
	TCCR0B |= (1 << CS02) | (0 << CS01) | (1 << CS00);
	// omogu?iti prekid za timer0 - overflow
	TIMSK0 |= (1 << TOIE0);
*/
	// inicijalizacija za timer0 - treci nacin
/*	// postaviti normalna nacin rada za timer0
	reset_bit_reg(TCCR0A, WGM00); //WGM00 = 0
	reset_bit_reg(TCCR0A, WGM01); //WGM01 = 0
	reset_bit_reg(TCCR0B, WGM02); //WGM02 = 0
	//postaviti djelitelj frekvencije na 1024
	set_bit_reg(TCCR0B, CS00); // CS00 = 1
	reset_bit_reg(TCCR0B, CS01);// CS01 = 0
	set_bit_reg(TCCR0B, CS02);// CS02 = 1
	// omoguciti prekid za timer0 - overflow
	set_bit_reg(TIMSK0, TOIE0);// TOIE0 = 1
*/		
	lcd_init(); // inicijalizacija lcd displeja
	interrupt_enable(); // globalno omoguci prekide //sei();
	TCNT0 = 22; // pocetna vrijednost registra
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