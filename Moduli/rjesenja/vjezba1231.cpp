/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 12.3.1
 */ 

#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
#include "LCD/lcd.h"
#include "Timer/timer.h"
#include "Interrupt/interrupt.h"
#include "ADC/adc.h"

volatile uint32_t broj_impulsa = 0;
bool hcsr04_measured = false;
volatile bool hcsr04_triggered = false;

// prekidna rutina za INT6
ISR(INT6_vect) {
	// ako je brid rastuci
	if(get_pin(PINE,PE6) == 1) {
		TCNT1 = 0; // t1 = 0
	}
	else {// ako je brid padajuci
		broj_impulsa = TCNT1;
		hcsr04_measured = true;
	}
}

void inicijalizacija() {
	
	lcd_init(); // inicijalizacija LCD displeja	
	adc_init(); // inicijalizacija AD pretvorbe
	// oba brida generiraju prekid INT6
	int6_set_rising_falling_edge();
	int6_enable();
	// tajmer 1 u normalnom nacinu rada
	timer1_set_normal_mode();
	timer1_set_prescaler(TIMER1_PRESCALER_8); //F_CPU/8
	// konfiguracija pinova za hcsr04
	output_port(DDRD,PD4); // trigg pin (PD4) - izlazni pin 
	input_port(DDRE,PE6); // echo pin (PE6) - ulazni pin 
	interrupt_enable(); // omoguci prekide
}

void hcsr04_trigg() {
	set_port(PORTD, 4, 1);
	_delay_us(20); // trigger impuls 20 us
	set_port(PORTD, 4, 0);
	hcsr04_triggered = true;
}

int main(void) {

	inicijalizacija();
	
	float d, d_cor; // udaljenost
	float t_echo; // trajanje impulsa na Echo pinu
	uint16_t time_delay = 0;
	uint16_t ADC_4; // vrijednost AD pretvorbe na pinu ADC4 
	float T; // temperatura 	
	float v_z; // brzina zvuka u zraku
	
	while(1) {
		// ako nije poslan trigg i ako je istekla 1 s
		if(!hcsr04_triggered && time_delay == 0) {
			hcsr04_trigg();	// posalji trigg signal na hcsr04
		}
		// ako je mjerenje zavrseno
		if(hcsr04_measured) {
			t_echo = broj_impulsa * 8.0 / F_CPU; // impuls Echo u s	 
			v_z = 343.0; // brzina zvuka na 20°C	
			d =  t_echo / 2.0 * v_z * 100.0; // udaljenost u cm
			ADC_4 = adc_read(ADC4); // AD pretvorba na kanalu ADC4
			// temperatura NTC otpornika
			T = 3435 / (log(ADC_4 / (1023.0 - ADC_4)) + 10.861) - 273.15;
			v_z = 331.0 + 0.6 * T; // brzina zvuka na temperaturi T
			d_cor =  t_echo / 2.0 * v_z * 100.0; // udaljenost u cm
			lcd_clrscr();
			lcd_home();
			lcd_print("d1 = %0.2f cm\n", d);
			lcd_print("d2 = %0.2f cm", d_cor);
			hcsr04_measured = false;
			hcsr04_triggered = false;
		}
		_delay_ms(10);
		// ako je prosla 1 s, vrati brojac vremena na 0 s
		if(++time_delay > 100) {
			time_delay = 0;
		}	
	}
}
