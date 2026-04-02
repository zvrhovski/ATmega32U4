/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 5.1.6
 */ 

#include "AVR VUB/avrvub.h"
#include "LCD/lcd.h"
#include <avr/io.h>

void inicijalizacija() {

	lcd_init(); // inicijalizacija lcd displeja
	lcd_define_char(); //definiranje novih znakova
}

int main(void) {
	
	inicijalizacija();
	
	lcd_clrscr();
	lcd_home();
	lcd_char(0x00);
	lcd_print("%c%c%c%c%c%c%c", 0x01,0x02,0x03,0x04,0x05,0x06,0x07);

	return 0;
}