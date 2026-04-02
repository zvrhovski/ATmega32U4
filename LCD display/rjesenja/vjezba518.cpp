/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 5.1.8
 */ 

#include "AVR VUB/avrvub.h"
#include "LCD/lcd.h"
#include <avr/io.h>
#include <util/delay.h>

void inicijalizacija() {
	
	lcd_init(); // inicijalizacija LCD displeja
}

int main(void) {
	
	inicijalizacija();
	
	lcd_clrscr();
	lcd_home();
	lcd_print("Materijali se nalaze na web stranici:\n");
	lcd_print("www.vub.hr/mikroracunala");
	
	while (1) {
		lcd_instr(LCD_ENTRY_INC_SHIFT);
		lcd_instr(LCD_MOVE_DISP_LEFT);
		_delay_ms(1000);
	}
	return 0;
}