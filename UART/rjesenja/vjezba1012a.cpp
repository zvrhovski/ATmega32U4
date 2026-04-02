/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 10.1.2 - drugi nacin
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
	// PB4, PB5, PB6, PB7 konfigurirani kao izlazni pinovi
	DDRB |= (1 << PB4) | (1 << PB5) | (1 << PB6) | (1 << PB7);
}

int main(void) {
	
	inicijalizacija();
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
			
			if (B == 'B' && (x >= '4' && x <= '7')) { 
				if(y == '0' || y == '1') {
					set_port(PORTB, x - 48, y - 48);
				}
			}
		}
	}
	return 0;
}