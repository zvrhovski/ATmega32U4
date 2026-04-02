/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 5.1
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
	
	while(1) {
		
		lcd_clrscr();  
		lcd_home();    
		lcd_print("Ivica\nIvic");
		_delay_ms(2000);
		
		lcd_clrscr();
		lcd_home();
		lcd_gotoxy(0,1);
		lcd_print("Veleuciliste u");
		lcd_gotoxy(1,3);
		lcd_print("Bjelovaru");
		_delay_ms(2000);	
	}
	return 0;	
}