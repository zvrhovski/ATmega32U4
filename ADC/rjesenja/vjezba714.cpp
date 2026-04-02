/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 7.1.4
 */ 

#include "AVR VUB/avrvub.h"
#include "LCD/lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include "ADC/adc.h"

void inicijalizacija() {
	
	lcd_init(); // inicijalizacija lcd displeja
	adc_init(); // inicijalizacija AD pretvorbe
}

int main(void) {
	
	inicijalizacija();

	uint16_t ADC_5; // vrijednost AD pretvorbe na pinu ADC5
	float U_ADC5; // napon na pinu ADC5
	const float V_REF = 5.0; // AVCC je referentni napon
	float u, p; // napon i tlak	
	
	while(1) {
		
		ADC_5 = adc_read(ADC5);
		U_ADC5 = ADC_5 * V_REF / 1023.0;
		u = U_ADC5;
		
		if (u <= 2.0) {
			p = 9 * u / 2 + 1;
		}
		else {
			p = 5 * u / 3 + 20.0 / 3;
		}

		lcd_clrscr();
		lcd_home();
		lcd_print("UADC5 = %.3fV", U_ADC5);
		lcd_print("\nTlak = %.3fbar", p);
		_delay_ms(1000);
	}
	return 0;
}