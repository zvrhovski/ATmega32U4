/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 7.1.2
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
	
	while(1) {
		
		ADC_5 = 0;
		
		for(uint8_t i = 0; i < 10; i++) {
			ADC_5 = ADC_5 + adc_read(ADC5); // ADC na kanalu ADC5
			_delay_ms(100);
		}
		
		ADC_5 = ADC_5 / 10;
		U_ADC5 = ADC_5 * V_REF / 1023; // pretvorba u napon

		lcd_clrscr();
		lcd_home();
		lcd_print("ADC5 = %d", ADC_5);
		lcd_print("\nUADC5 = %.2fV", U_ADC5);
	}
	return 0;
}