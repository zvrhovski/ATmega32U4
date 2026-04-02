/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 8.2.6
 */

#include "AVR VUB/avrvub.h"
#include <avr/io.h>
#include <util/delay.h>
#include "Timer/timer.h"
#include "LCD/lcd.h"
#include "ADC/adc.h"

void inicijalizacija() {
	// inicijalizacija za timer 1 - Phase Correct PWM 
	timer1_set_prescaler(TIMER1_PRESCALER_64);
	timer1_set_phase_correct_PWM_8bit(); // raspon brojanja [0, 255]
	//timer1_set_phase_correct_PWM_9bit(); // raspon brojanja [0, 511]
	//timer1_set_phase_correct_PWM_10bit(); // raspon brojanja [0, 1023]
	//timer1_set_phase_correct_PWM_ICR1(2500); // raspon brojanja [0, ICR1]
	timer1_OC1A_enable_non_inverted_PWM();
	
	DDRB |=  (1 << PB5); //PB5 izlazni pin			
	adc_init(); // inicijalizacija AD pretvorbe
	lcd_init(); // inicijalizacija LCD displeja
}

int main(void) {
		
	inicijalizacija();
	uint16_t pwm_bit;
	float duty;
	
	while(1) {
	
		pwm_bit = PWM_8BIT;
		//pwm_bit = PWM_9BIT;
		//pwm_bit = PWM_10BIT;
		//pwm_bit = PWM_ICR1;
		duty = adc_read(ADC5)*100.0/1023.0;
		OC1A_set_duty_cycle(duty, pwm_bit);
				
		lcd_clrscr();
		lcd_home();
		lcd_print("PWM freq:%luHz\n", F_CPU / 64 / (2 * pwm_bit));
		lcd_print("TD/T:%.2f%%", duty);
		_delay_ms(500);
	}
	return 0;
}