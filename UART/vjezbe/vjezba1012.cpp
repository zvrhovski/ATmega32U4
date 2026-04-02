/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 10.1.2
 */ 

#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
#include "LCD/lcd.h"
#include "UART/uart.h"
#include "Interrupt/interrupt.h"
#include "DigitalIO/DigitalIO.h"

void inicijalizacija() {
	uart_init(19200); //inicijalizacija serijske komunikacije
	lcd_init(); // konfiguriranje LCD displeja
	interrupt_enable(); //omoguci globalni prekid
}

int main(void) {
	
	inicijalizacija();
	// stvaranje objekata za LED diode
	DigitalOutput LED_crvena(B4); // pin PB4 - crvena dioda
	DigitalOutput LED_zuta(B5); // pin PB5 - zuta dioda
	DigitalOutput LED_zelena(B6); // pin PB6 - zelena dioda
	DigitalOutput LED_plava(B7); // pin PB7 - plava dioda
	char B, x, y;
	
	while(1) {
		// provjera primljenih poruka
		if(uart_read_all() == true) {
			lcd_clrscr();
			lcd_home();
			lcd_print("%s", uart_buffer);			
			B = uart_buffer[0];
			x = uart_buffer[1];
			y = uart_buffer[2];
			// provjera prvog znaka
			if (B == 'B') { 
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
						if (y == '1') LED_plava.on();
						if (y == '0') LED_plava.off();
						break;
					default:
						break;
				}
			}
		}
	}
	return 0;
}