/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 10.1.4
 */ 

#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
// ukljucite potrebna zaglavlja

uint32_t vrijeme = 0;
DigitalOutput LED_crvena(B4); // pin PB4 - crvena dioda

ISR(TIMER1_OVF_vect){
	TCNT1 = 0;
	vrijeme++; // mjerenje vremena rada uC-a
	LED_crvena.toggle(); //promjena stanja crvene diode
}

void inicijalizacija() {
	// inicijalizacija serijske komunikacije
	// konfiguriranje LCD displeja
	// konfiguriranje AD pretvorbe
	// omoguci globalni prekid
	// konfiguriranje tajmera 1
	timer1_set_normal_mode();
	timer1_set_prescaler(TIMER1_PRESCALER_1024);
	timer1_interrupt_OVF_enable();
	TCNT1 = 0;
}

int main(void) {
	
	inicijalizacija();
	DigitalInput Tipkalo_D0(D0); // pin PD0 - tipkalo 
	Tipkalo_D0.pullup_on(); // ukljuci pull up na PD0 
	uint16_t ADC_4, ADC_5; // vrijednost AD pretvorbe na pinu ADC4 i ADC5
	float T, U_ADC5; // temperatura i napon
	
	while(1) {
		// provjera primljenih poruka
		if(uart_read_all() == true) {
			lcd_clrscr();
			lcd_home();
			lcd_print("%s", uart_buffer);			
			// provjera da li je drugi znak '\0' - kraj stringa
			if (uart_buffer[1] == '\0') { 
				// automat stanja koji obraduje prvi znak poruke
				switch(uart_buffer[0]) {
					case 'P':
						uart_print("ATmega32U4\r");
						break;
					case 'C':
						//posalji stanje crvene LED diode
						break;
					case 'D':
						//posalji stanje tipkala na PD0
						break;
					case 'A':
						// napravite AD pretvorbu na ADC5
						// posalji ADC5
						break;
					case 'N':
						// napravite AD pretvorbu na ADC5
						// izracunajte i posaljite napon U_ADC5
						break;
					case 'T':
						// napravite AD pretvorbu na ADC4
						// izracunajte i posaljite temperaturu
						break;
					case 'V':
						// posaljite vrijeme rada mikroupravljaca
						break;
					default:
						uart_print("Neispravan unos!\r");
						break;
				}
			}
		}
	}
	return 0;
}
