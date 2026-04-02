/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 4.1.7
 */  

#include "AVR VUB/avrvub.h"
#include <avr/io.h>
#include <util/delay.h>


int main(void) {
	
	while (1) { // beskonacna petlja
	
		//super mario sound - isjecak
		BUZZ(0.1, 660); _delay_ms(150);
		BUZZ(0.1, 660);	_delay_ms(300);
		BUZZ(0.1, 660);	_delay_ms(300);
		BUZZ(0.1, 510);	_delay_ms(100);
		BUZZ(0.1, 660);	_delay_ms(300);
		BUZZ(0.1, 770);	_delay_ms(550);
		BUZZ(0.1, 770);	_delay_ms(575);	
		BUZZ(0.1, 510);	_delay_ms(450);	
		BUZZ(0.1, 380);	_delay_ms(400);	
		BUZZ(0.1, 320);	_delay_ms(500);
		BUZZ(0.1, 440);	_delay_ms(300);	
		BUZZ(0.08, 480);_delay_ms(330);
		BUZZ(0.1, 450);	_delay_ms(150);
		BUZZ(0.1, 430);	_delay_ms(300);
		BUZZ(0.1, 380);	_delay_ms(200);
		BUZZ(0.08, 660);_delay_ms(200);
		BUZZ(0.1, 760);	_delay_ms(150);
		BUZZ(0.1, 860);	_delay_ms(300);
		BUZZ(0.08, 700);_delay_ms(150);		
		BUZZ(0.05, 760);_delay_ms(350);
		BUZZ(0.08, 660);_delay_ms(300);
		BUZZ(0.08, 520);_delay_ms(150);
		BUZZ(0.08, 580);_delay_ms(150);	
		BUZZ(0.08, 480);_delay_ms(1000);		
	}
	return 0;
}