/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 10.1.3
 */ 

#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
#include "LCD/lcd.h"
#include "UART/uart.h"
#include "Interrupt/interrupt.h"
#include "DigitalIO/DigitalIO.h"
#include "Timer/timer.h"

void inicijalizacija() {
	uart_init(38400); //inicijalizacija serijske komunikacije
	lcd_init(); // konfiguriranje LCD displeja
	interrupt_enable(); //omoguci globalni prekid
	timer0_set_phase_correct_PWM();
	timer0_set_prescaler(TIMER0_PRESCALER_8);
	timer0_OC0A_enable_non_inverted_PWM(); //timer0_OC0A_disable();
}

int main(void) {
	
	inicijalizacija();
	// stvaranje objekata za LED diode
	DigitalOutput LED_crvena(B4); // pin PB4 - crvena dioda
	DigitalOutput LED_zuta(B5); // pin PB5 - zuta dioda
	DigitalOutput LED_zelena(B6); // pin PB6 - zelena dioda
	DigitalOutput LED_plava(B7); // pin PB7 - plava dioda
	char key_char, x, y;
	uint8_t slider = 0;
	
	while(1) {
		// provjera primljenih poruka
		if(uart_read_all() == true) {
			lcd_clrscr();
			lcd_home();
			lcd_print("%s", uart_buffer);			
			key_char = uart_buffer[0];
			// provjera prvog znaka
			if (key_char == 'B') { 
				x = uart_buffer[1];
				y = uart_buffer[2];
				// automat stanja koji obraduje ostatak poruke tipa "xy"
				switch(x) {
					case '4':
						if (y == '1') LED_crvena.on();
						if (y == '0') LED_crvena.off();
						break;
					case '5':
						if (y == '1') LED_zuta.on();
						if (y == '0') LED_zuta.off();
						break;
					case '6':
						if (y == '1') LED_zelena.on();
						if (y == '0') LED_zelena.off();
						break;
					case '7':
						if (y == '1') LED_plava.enable(); //timer0_OC0A_enable_non_inverted_PWM();
						if (y == '0') LED_plava.disable(); //timer0_OC0A_disable();
						break;
					default:
						break;
				}
			}
			
			if (key_char == 'S') {
				for(uint8_t i = 1; uart_buffer[i] != '*'; i++) {
					slider = slider * 10 + (uart_buffer[i] - 48);
				}
				OC0A_set_duty_cycle(slider/2.55);
				slider = 0;
			}
		}
	}
	return 0;
}
