/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 12.1.1 - dvokvadrantni nacin rada
 */ 

#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
#include "LCD/lcd.h"
#include "Timer/timer.h"
#include "Interrupt/interrupt.h"
#include "DigitalIO/DigitalIO.h"

// ulazi za rotacijski enkoder
DigitalInput Encoder_ChannelA(D0);
DigitalInput Encoder_ChannelB(D1);
DigitalInput Encoder_PushButton(F7);

int8_t encoder_position = 0;
bool new_position = true;

#define ENCODER_LOW_LEVEL 0
#define ENCODER_HIGH_LEVEL 100

void encoder_inc_dec(bool direction) {
	// direction = true - Smjer 1, direction = false - Smjer 2
	//Smjer 1 - u smjeru kazaljke na satu
	//Smjer 2 - suprotno smjeru kazaljke na satu
	if(direction == false) {
		if (encoder_position < ENCODER_HIGH_LEVEL) {
			encoder_position++;
		}
	}
	else {
		if(encoder_position > ENCODER_LOW_LEVEL) {
			encoder_position--;
		}
	}
	new_position = true;	
}

// dvokvadrantni nacin rada, INT0 - rastuci i padajuci brid
ISR(INT0_vect) {
	
	bool direction; // direction = true - Smjer 1, direction = false - Smjer 2
	direction = Encoder_ChannelA.state() ^ Encoder_ChannelB.state();
	encoder_inc_dec(direction);
}

void inicijalizacija() {
	
	lcd_init(); //konfiguracije LCD displeja	
	int0_enable(); // omoguci INT0
	int0_set_rising_falling_edge(); // rastuci i padajuci brid generira prekid na INT0
	// pritezni otpornici na ulazima za rotacijski enkoder
	Encoder_ChannelA.pullup_on(); 
	Encoder_ChannelB.pullup_on();
	Encoder_PushButton.pullup_on();
	interrupt_enable();
}

int main(void){

	inicijalizacija();
	uint8_t loading = 0;	
	while(1) {
		
		if(new_position) {
			lcd_clrscr();
			lcd_home();
			lcd_print("%d\n", encoder_position);
			loading = 16*encoder_position/100.0;
			for(uint8_t i = 0; i < loading; i++) {
				lcd_char(255);	
			}
			new_position = false;
		}
		
		if(Encoder_PushButton.isFalling_edge()) {
			encoder_position = 0;		
			new_position = true;	
		}
	}
}