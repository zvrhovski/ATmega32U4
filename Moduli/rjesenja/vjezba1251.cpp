/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 12.5.1
 */ 

#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
#include "ADC/adc.h"
#include "Timer/timer.h"
#include "LCD/lcd.h"

#define DUTY_MIN 2.38  // sirina PWM signala za kut 0
#define DUTY_MAX 10.96 // sirina PWM signala za kut 180
#define DUTY_MID 6.037 // sirina PWM signala za kut 90

void set_servo_angle_2(float angle) {
	float duty;
	if(angle <= 90) {
		duty = DUTY_MIN + (DUTY_MID - DUTY_MIN) / 90 * angle;
	}
	else {
		duty = DUTY_MID + (DUTY_MAX - DUTY_MID) / 90 * (angle - 90);
	}
	OC1A_set_duty_cycle(duty, PWM_ICR1);
}

void set_servo_angle(float angle) {
	float duty = DUTY_MIN + (DUTY_MAX - DUTY_MIN) / 180 * angle;
	OC1A_set_duty_cycle(duty, PWM_ICR1);
}

void inicijalizacija(){
	lcd_init(); // inicijalizacija LCD displeja
	adc_init(); // inicijalizacija AD pretvorbe
	// timer 1 kao PWM 50 Hz
	timer1_set_prescaler(TIMER1_PRESCALER_64);
	timer1_set_phase_correct_PWM_ICR1(2500);
	timer1_OC1A_enable_non_inverted_PWM();
	DDRB |= (1 << PB5); // izlazni pin za servo motor (OC1A)
}

int main(void) {
	
	inicijalizacija();
	
	uint16_t ADC_5;
	float duty, angle;
	
	while(1) {
		
		ADC_5 = adc_read(ADC5); // AD pretvorba na pinu ADC5
		//duty = DUTY_MIN + (DUTY_MAX - DUTY_MIN) * ADC_5 / 1023.0; // D = [2.0, 12.5] (0.4 ms - 2.5 ms)
		//OC1A_set_duty_cycle(duty, PWM_ICR1); // postavi duty cycle na kanalu OC1A
		angle = ADC_5 / 1023.0 * 180;
		set_servo_angle_2(angle);
		
		lcd_clrscr();
		lcd_home();
		//lcd_print("duty = %0.3f\n", duty);
		lcd_print("kut = %0.2f%c\n", angle, 223);
		_delay_ms(500);
	}
	return 0;
}