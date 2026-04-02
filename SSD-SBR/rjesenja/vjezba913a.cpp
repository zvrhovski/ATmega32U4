/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 9.1.3 - na?in s tajmerima
 */ 

#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
#include "DigitalIO/DigitalIO.h"
#include "SSD i SBR/ssd_sbr.h"
#include "Timer/timer.h"
#include "Interrupt/interrupt.h"

uint16_t desetinke = 0;
bool count_up = true;
bool new_time_ready = false;

ISR(TIMER1_OVF_vect) {
	TCNT1 = 40536;
	new_time_ready = true;
	if(count_up) {
		if (++desetinke > 9999) {
			desetinke = 0;
		}
	}
	else {
		if (--desetinke == 65535) {
			desetinke = 9999;
		}
	}	
}

void inicijalizacija(){
	// normalna nacin rada - timer 1
	timer1_set_normal_mode();
	timer1_set_prescaler(TIMER1_PRESCALER_64); 
	TCNT1 = 40536;
	interrupt_enable();
}

int main(void) {
	
	inicijalizacija();
	
	// stvaranje objekta za posmacni registar
	Shift_Bit_Register SBR(C7, F1, F0);
	DigitalInput StartStop(D0); // PD0 ulazni pin
	DigitalInput Clear(D1); // PD1 ulazni pin
	DigitalInput Direction(F6); // PF6 ulazni pin
	
	StartStop.pullup_on(); //pull up na PD0
	Clear.pullup_on(); //pull up na PD1
	Direction.pullup_on(); //pull up na PF6
	
	bool counting = false;
	uint8_t d1 = 0, d2 = 0, d3 = 0, d4 = 0;
	// slanje cetiri bajta na posmacne registre
	SBR.send_4byte(digits[d1], digits[d2], digits[d3] | DOT, digits[d4]);
			
	while(1) {
		// na padajuci brid tipkala StartStop
		if(StartStop.isFalling_edge()) {
			if (counting)	{
				counting = false;
				timer1_interrupt_OVF_disable();
			}
			else {
				counting = true;
				timer1_interrupt_OVF_enable();	
			}
		} 
		// na padajuci brid tipkala Direction
		if(Direction.isFalling_edge()) {
			if (count_up)	{
				count_up = false;
			}
			else {
				count_up = true;
			}
		}
		// na padajuci brid tipkala Clear
		if(Clear.isFalling_edge()) {
			desetinke = 0;
			d1 = d2 = d3 = d4 = 0;
			SBR.send_4byte(digits[d1], digits[d2], digits[d3] | DOT, digits[d4]);
		}
		// ako je tajmer generirao novih 100 ms, prikazi ih				
		if (new_time_ready)	{
			// racunanje znamenaka 
			d1 = desetinke / 1000;
			d2 = (desetinke / 100) % 10;
			d3 = (desetinke / 10) % 10;
			d4 = desetinke % 10;
			
			SBR.send_4byte(digits[d1], digits[d2], digits[d3] | DOT, digits[d4]);
			new_time_ready = false;
		}
	}
	return 0;
}

