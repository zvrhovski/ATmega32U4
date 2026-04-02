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
	TCNT1 = 15536; // pocetna vrijednost registra
	toggle_port(PORTB, PB5);
}

void inicijalizacija() {
	DDRB |= (1 << PB5); // PB5 izlazni pin
	// inicijalizacija za timer1 - prvi nacin
	timer1_set_normal_mode();
	timer1_set_prescaler(TIMER1_PRESCALER_64);
	timer1_interrupt_OVF_enable();

/*	// inicijalizacija za timer1 - treci nacin
	// postaviti normalna nacin rada za timer1
	reset_bit_reg(TCCR1A, WGM10); //WGM10 = 0
	reset_bit_reg(TCCR1A, WGM11); //WGM11 = 0
	reset_bit_reg(TCCR1B, WGM12); //WGM12 = 0
	reset_bit_reg(TCCR1B, WGM13); //WGM13 = 0
	//postaviti djelitelj frekvencije na 64
	set_bit_reg(TCCR1B, CS10); // CS10 = 1
	set_bit_reg(TCCR1B, CS11);// CS11 = 1
	reset_bit_reg(TCCR1B, CS12);// CS12 = 0
	// omogu?iti prekid za timer1 - overflow
	set_bit_reg(TIMSK1, TOIE1);// TOIE1 = 1
*/	
	lcd_init(); // inicijalizacija lcd displeja
	interrupt_enable(); // globalno omoguci prekide //sei();
	TCNT1 = 15536; // pocetna vrijednost registra
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