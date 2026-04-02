/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 8.2.2
 */ 

#include "AVR VUB/avrvub.h"
#include <avr/io.h>
#include <util/delay.h>
#include "Timer/timer.h"
#include "LCD/lcd.h"
#include "ADC/adc.h"

void inicijalizacija() {
	// inicijalizacija za timer 0 - neinvertirajuci Fast PWM
	timer0_set_prescaler(TIMER0_PRESCALER_8);
	timer0_set_fast_PWM();
	timer0_OC0A_enable_non_inverted_PWM();
	
	output_port(DDRB,PB7);	
	lcd_init();
	adc_init();
}

int main(void) {
		
	inicijalizacija();
	
	float duty; // sirina impulsa
	uint16_t ADC_5; // vrijednost AD pretvorbe na pinu ADC5
	
	while(1) {
		
		ADC_5 = adc_read(ADC5); // ADC na kanalu ADC5
		duty = ADC_5 *100.0/1023.0;
		OC0A_set_duty_cycle(duty);
		
		lcd_clrscr();
		lcd_home();
		lcd_print("PWM freq:%luHz\n", F_CPU / 8 / 256);
		lcd_print("TD/T:%.2f%%", duty);
		_delay_ms(500);
		
	}
	return 0;
}