/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 8.2.1
 */ 

#include "AVR VUB/avrvub.h"
#include <avr/io.h>
#include <util/delay.h>
#include "Timer/timer.h"

void inicijalizacija() {
	// inicijalizacija za timer 0 - neinvertirajuci Fast PWM
	timer0_set_prescaler(TIMER0_PRESCALER_8);
	timer0_set_fast_PWM();
	timer0_OC0A_enable_non_inverted_PWM();
	
	output_port(DDRB,PB7);	
	
	/*
	// inicijalizacija za timer 0 - neinvertirajuci Fast PWM (drugi nacin)
	TCCR0B |= (0 << CS02) | (1 << CS01) | (0 << CS00);  //F_CPU/8
	TCCR0A |= (1 << WGM01) | (1 << WGM00);  // Fast PWM nacin rada
	TCCR0B |= (0 << WGM02);  // VRH je 0x0FF
	TCCR0A |= (1 << COM0A1) | (0 << COM0A0); // Neinvertiraju?i PWM

	DDRB |= (1 << PB7);
	*/
}

int main(void) {
		
	inicijalizacija();
		
	while(1) {
		OCR0A = 26;
		//OC0A_set_duty_cycle(10.0); // drugi nacin promjene sirine PWM signala
		_delay_ms(1000);
		OCR0A = 102;
		//OC0A_set_duty_cycle(40.0)
		_delay_ms(1000);
		OCR0A = 230;
		//OC0A_set_duty_cycle(90.0)
		_delay_ms(1000);
	}
	return 0;
}