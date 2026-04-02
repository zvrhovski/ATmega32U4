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
	int32_t c = -265972;
	uint32_t d = 5600300;
	
	while (1) {
		lcd_clrscr();
		lcd_home();
		lcd_print("int: %d \n", a);
		lcd_print("float: %0.2f ", b);
		_delay_ms(2000);
		lcd_clrscr();
		lcd_home();
		lcd_print("int32_t:%ld\n", c);
		lcd_print("uint32_t:%luf", d);
		_delay_ms(2000);
		
	}
	return 0;	
}