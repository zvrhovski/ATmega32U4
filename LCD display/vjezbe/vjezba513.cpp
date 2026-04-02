/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 5.1.3
 */ 

#include "AVR VUB/avrvub.h"
#include <avr/io.h>


void inicijalizacija() {
	
}

int main(void) {
	
	inicijalizacija();
	
	char a = 'A';
	
	while (1) {
		
		lcd_clrscr();
		lcd_home();
		lcd_print("Veliko slovo: %c\n", a);
		lcd_print("Malo slovo:");
		
		_delay_ms(1000);
		
		if (++a > 'Z') {
			a = 'A';
		}
	}
	return 0;    
}