/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 5.1.7
 */ 

#include "AVR VUB/avrvub.h"
#include "LCD/lcd.h"
#include <avr/io.h>
#include <util/delay.h>

void inicijalizacija() {
	
	lcd_init(); // inicijalizacija lcd displeja
	lcd_define_char(); //definiranje novih znakova
}

int main(void) {
	
	inicijalizacija();
	
	while (1) {
		lcd_clrscr();
		lcd_home();
		lcd_gotoxy(0,2);
		lcd_print("Veleu");
		lcd_char(0x00); // znak ?c je na adresi 0x00
		lcd_print("ili%cte", 0x02); // znak ?š je na adresi 0x02
		lcd_gotoxy(1,2);
		lcd_print("u Bjelovaru"); 
		_delay_ms(2000);

		lcd_clrscr();
		lcd_home();
		lcd_gotoxy(0,1);
		lcd_print("Stru");
		lcd_char(0x00); // znak è
		lcd_print("ni studij");
		lcd_gotoxy(1,2);
		lcd_print("Mehatronika");
		_delay_ms(2000);
		
		lcd_clrscr();
		lcd_home();
		lcd_gotoxy(0,1);
		lcd_print("Stru");
		lcd_char(0x00);
		lcd_print("ni studij");
		lcd_gotoxy(1,2);
		lcd_print("Ra");
		lcd_char(0x00);
		lcd_print("unarstvo");
		_delay_ms(2000);
	}
	return 0;
}