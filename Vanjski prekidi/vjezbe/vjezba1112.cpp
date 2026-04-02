/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 11.1.2
 */ 

#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
#include "Interrupt/interrupt.h"
#include "DigitalIO/DigitalIO.h"

DigitalOutput LED_crvena(B4);
DigitalOutput LED_zuta(B5);
DigitalOutput LED_zelena(B6);
DigitalOutput LED_plava(B7);
	
uint8_t pinb_old;

ISR(PCINT0_vect) {
	
	uint8_t pin_changed = pinb_old ^ PINB;
	
	if (pin_changed & (1 << PB4)) {
		LED_zuta.toggle();
	}

	if (pin_changed & (1 << PB6)) {
		if ((pinb_old & (1 << PB6))) {
			LED_plava.off();
		} else {
			LED_plava.on();	
		}
	}
		
	pinb_old = PINB;
}

void inicijalizacija() {

	//omoguci PCINT prekide
	pcint_enable();
	//omoguci prekide na pinovima PCINT4 (PB4) i PCINT6 (PB6)
	pcint_pin_enable(PCINT4);
	pcint_pin_enable(PCINT6);
	
	pinb_old = PINB;
	interrupt_enable(); //omoguci globalni prekid
}

int main(void) {
	
	inicijalizacija();
	uint8_t brojac = 0;
	
	while(1) {
		
		brojac++;
		
		if ((brojac % 5) == 0) LED_crvena.toggle();
		if ((brojac % 9) == 0) LED_zelena.toggle();
	
		_delay_ms(100);		
	}
	return 0;
}