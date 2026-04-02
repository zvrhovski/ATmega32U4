/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 5.1.2
 */ 

#include "AVR VUB/avrvub.h"
#include "LCD/lcd.h"
#include <avr/io.h>
#include <util/delay.h>

void inicijalizacija() {
	
	lcd_init(); // inicijalizacija lcd displeja
}

int main(void) {
	
	inicijalizacija();
	
	// deklaracija podataka
	int a = -123;
	float b = 3.14;
	
	while (1) {
		lcd_clrscr();
		lcd_home();
		lcd_print("int: %d \n", a);
		lcd_print("float: %0.2f ", b);
	
	}
	return 0;	
}