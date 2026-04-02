/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 6.1.1
 */ 

#include "AVR VUB/avrvub.h"
#include "LCD/lcd.h"
#include <avr/io.h>
#include <avr/eeprom.h>

int8_t cijeli8_t;
int16_t cijeli16_t;
int32_t cijeli32_t;
float realan;

void inicijalizacija() {
	
	input_port(DDRD,PD0);
	set_port(PORTD,PD0,1);
	
	cijeli8_t = eeprom_read_byte(addr_byte(0x00));
	cijeli16_t = eeprom_read_word(addr_word(0x01));
	cijeli32_t = eeprom_read_dword(addr_dword(0x03));
	realan = eeprom_read_float(addr_float(0x07));
	
	lcd_init();
}

int main(void) {
	
	inicijalizacija();
	
	while(1) {
		
		cijeli8_t++;
		cijeli16_t +=2;
		cijeli32_t +=3;
		realan = 1.1 * cijeli8_t;
		
		// ispitivanje padajuceg brida na PD0
		if(isFalling_edge(PD, PD0) == true) {
			eeprom_write_byte(addr_byte(0x00),cijeli8_t);
			eeprom_write_word(addr_word(0x01),cijeli16_t);
			eeprom_write_dword(addr_dword(0x03),cijeli32_t);
			eeprom_write_float(addr_float(0x07),realan);
		}
		
		lcd_clrscr();
		lcd_home();
		lcd_print("C8: %d,C16: %d", cijeli8_t, cijeli16_t);
		lcd_print("\nC32: %ld,R: %.2f", cijeli32_t, realan);
		_delay_ms(1000);
	}
	return 0;
}