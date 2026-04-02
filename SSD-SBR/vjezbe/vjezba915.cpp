/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 9.1.5
 */ 
#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
#include "DigitalIO/DigitalIO.h"
#include "SSD i SBR/ssd_sbr.h"

int main(void) {
	// stvaranje objekta za posmacni registar
	Shift_Bit_Register SBR(C7, F1, F0);

	while(1) {
		// slanje definiranih znakova na numericke displeje
		SBR.send_4byte(DIGIT_2, DIGIT_5, BIG_DEEGRE, CHAR_C);
		_delay_ms(1000);
		SBR.send_4byte(EMPTY_SPACE, CHAR_A, CHAR_H, EMPTY_SPACE);
		_delay_ms(1000);
		SBR.send_4byte(MINUS, DIGIT_1, DIGIT_2 | DOT, DIGIT_3);
		_delay_ms(1000);
	}
	return 0;
}