/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 8.2.3
 */

#include "AVR VUB/avrvub.h"
#include <avr/io.h>
#include <util/delay.h>
#include "Timer/timer.h"
#include "LCD/lcd.h"
#include "ADC/adc.h"

void inicijalizacija() {
	// inicijalizacija za timer 1 - Fast PWM
	timer1_set_prescaler(TIMER1_PRESCALER_64);
	timer1_set_fast_PWM_8bit();
	timer1_OC1A_enable_non_inverted_PWM();
	timer1_OC1B_enable_inverted_PWM();
	timer1_OC1C_enable_non_inverted_PWM();
	
	DDRB |= (1 << PB5) | (1 << PB6) | (1 << PB7);
					
	adc_init(); // inicijalizacija AD pretvorbe
	lcd_init(); // inicijalizacija LCD displeja
}

int main(void) {
		
	inicijalizacija();

	float duty;

	while(1) {
	
		duty = adc_read(ADC5)*100.0/1023.0;
		OC1A_set_duty_cycle(duty, PWM_8BIT);
		OC1B_set_duty_cycle(duty, PWM_8BIT);
		OC1C_set_duty_cycle(duty, PWM_8BIT);
				
		lcd_clrscr();
		lcd_home();
		lcd_print("PWM freq:%luHz\n", F_CPU / 64 / 256);
		lcd_print("TD/T:%.2f%%", duty);
		_delay_ms(500);
	}
	return 0;
}