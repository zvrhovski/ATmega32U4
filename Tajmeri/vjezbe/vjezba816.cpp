/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 8.1.6
 */ 

#include "AVR VUB/avrvub.h"
#include <avr/io.h>
// ukljuci sva potrebna zaglavlja

uint8_t uzorak_procitan = 0; // logicka varijabla
uint16_t ADC_5; // vrijednost AD pretvorbe na pinu ADC5

// prekidna rutina za timer3
ISR(TIMER3_OVF_vect) { 
	TCNT3 = 0; // pocetna vrijednost registra
	ADC_5 = adc_read(ADC5); // ADC na kanalu ADC5
	uzorak_procitan = 1;
}

void inicijalizacija() {
	
	// inicijalizacija za timer3
	
	// inicijalizacija lcd displeja
	// inicijalizacija AD pretvorbe
	
	// globalno omoguci prekide //sei();
	TCNT3 = 0; // pocetna vrijednost registra
}

int main(void) {
		
	inicijalizacija();
	
	float U_ADC5; // napon na pinu ADC5
	const float V_REF = 5.0; // AVCC je referentni napon
	
	DigitalInput tipka(D0);
	tipka.pullup_on();

	while(1) {
		
		if(tipka.state() == false)	{
			timer3_interrupt_OVF_enable();
		}
		else {
			timer3_interrupt_OVF_disable();
			lcd_clrscr();
		}	
		if(uzorak_procitan == 1) {
			U_ADC5 = ADC_5 * V_REF / 1023; // pretvorba u napon
			lcd_clrscr();
			lcd_home();
			lcd_print("UADC5 = %.2fV", U_ADC5);
			uzorak_procitan = 0;
		}
	}
	return 0;
}