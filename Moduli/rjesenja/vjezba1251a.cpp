/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 12.5.1 - kontinuirano gibanje izlazne osovine servo motora
 */ 

#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
#include "ADC/adc.h"
#include "Timer/timer.h"
#include "LCD/lcd.h"

#define D_MIN 2.38  // sirina PWM signala za kut 0
#define D_MAX 10.96 // sirina PWM signala za kut 180
#define D_MID 6.037 // sirina PWM signala za kut 90

void set_servo_angle_2(float angle) {
	float duty;
	if(angle <= 90) {
		duty = D_MIN + (D_MID - D_MIN) / 90 * angle;
	}
	else {
		duty = D_MID + (D_MAX - D_MID) / 90 * (angle - 90);
	}
	OC1A_set_duty_cycle(duty, PWM_ICR1);
}

void set_servo_angle(float angle) {
	float duty = D_MIN + (D_MAX - D_MIN) / 180 * angle;
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
	
	uint8_t i;
	// direction = true - gibanje od 0 do 180
	// direction = false - gibanje od 180 do 0
	bool direction = true;
	
	while(1) {
		// postavi zakret na servo motor
		set_servo_angle_2(i);
		// ako je zakret 0, pricekaj 500 ms i promijeni smjer
		if(i == 0) {
			direction = true;
			_delay_ms(500);
		}
		// ako je zakret 90, pricekaj 500 ms
		if(i == 90) _delay_ms(500);
		// ako je zakret 180, pricekaj 500 ms i promijeni smjer
		if(i == 180) {
			direction = false;
			_delay_ms(500);
		}
		// ako je direction = true povecavaj zakret, inace smanjuj
		if(direction) {
			i++;			
		}
		else {
			i--;
		}				
		_delay_ms(10);
	}
	return 0;
}