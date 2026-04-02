/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 12.4.1
 */ 

#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
#include "LCD/lcd.h"
#include "ADC/adc.h"

void inicijalizacija() {
	// konfigurirajte ADC i LCD
	lcd_init();
	adc_init();
}

int main(void) {
	
	inicijalizacija();

	uint16_t ADC_5; // vrijednost AD pretvorbe na pinu ADC5
	float U_ADC5; // napon na pinu ADC5
	const float V_REF = 5.0; // AVCC je referentni napon
	float T; // temperatura u okolini senzora LM35
	
	while (1) {
	
		ADC_5 = adc_read(ADC5);
		U_ADC5 = ADC_5 * V_REF / 1023.0;
		T = U_ADC5 * 100; // temperatura senzora LM35
		
		lcd_clrscr();
		lcd_home();
		lcd_print("T = %0.2f%cC\n", T, 223);
		_delay_ms(1000);
	}
	
	return 0;
}