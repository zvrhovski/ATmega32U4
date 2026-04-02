/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 10.1.1
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
	// stvaranje objekata za tipkala
	DigitalInput Tipkalo_D0(D0); // pin PD0
	DigitalInput Tipkalo_D1(D1); // pin PD1
	Tipkalo_D0.pullup_on(); // pritezni otpornik na pinu PD0
	Tipkalo_D1.pullup_on(); // pritezni otpornik na pinu PD1

	while(1) {
		// provjera primljenih poruka
		if(uart_read_all() == true) {
			lcd_clrscr();
			lcd_home();
			lcd_print("%s", uart_buffer);			
		}
		// provjera padajuceg brida tipkala na PDO
		if(Tipkalo_D0.isFalling_edge()) {
			uart_print("Serijska komunikacija je uspostavljena\r");
		}
		// provjera padajuceg brida tipkala na PD1
		if(Tipkalo_D1.isFalling_edge()) {
			uart_print("Baud rate je %u\r", 19200);
		}
	}
	return 0;
}