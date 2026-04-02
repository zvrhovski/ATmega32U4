/*
 * vjezba8_dodatak1.cpp
 *
 * Created: 4/1/2026 11:38:23 AM
 *  Author: Zoran
 */ 
#include "AVR VUB/avrvub.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/* ?? Interrupt Service Routines ??????????????????????????????????? */

ISR(TIMER1_COMPA_vect)
{
	PORTB ^= (1 << PB6);
}

void init(void)
{

	/* ---- Timer 1 (Timer 1  (16-bit))  |  CTC  (TOP = OCR1A)  |  clk / 1024  |  1.00 Hz ---- */
	TCCR1A = (1<<COM1A0);
	TCCR1B = (1<<WGM12) | (1<<CS10) | (1<<CS12);
	OCR1A  = 15624;  /* TOP */
	TIMSK1 |= (1<<OCIE1A);  /* compare match interrupt */
	DDRB  |= (1<<PB5);  /* OC1A (PB5, pin 28) output */
	DDRB  |= (1<<PB6);  /* OC1A (PB5, pin 28) output */

	sei();  /* enable global interrupts */
}


int main(void) {
	
	init();
	uint16_t minute = 0;
	
	while(1) {

		_delay_ms(1000);
	}
	return 0;
}