/*
 * avrvub.cpp
 *
 * Created: 6.3.2020. 12:09:23
 *  Author: Zoran Vrhovski
 */ 

#include "avrvub.h"
#include <util/delay.h>

void BUZZ(double duration, int freq){
	long int i,cycles;
	cycles = duration * freq; // broj ciklusa izmjena pina za zujalicu
	long int period = 1.0/freq * 100000; // izracun poluperioda
	long int half_period =  period / 2;
	BUZZER_DDR |= (1 << BUZZER_PIN);  // konfiguriranje izlaznog pina za zujalicu
	
	for (i=0; i < cycles; i++)   // mijenjaj stanje pina zujalice (cycles) puta
	{
		half_period = period/2;
		while(half_period--) {
			_delay_us(10);
		}
		
		BUZZER_PORT |= (1 << BUZZER_PIN);    // postavi pin zujalice
		
		half_period = period/2;
		while(half_period--) {
			_delay_us(10);
		}                       // cekaj poluperiodu
		BUZZER_PORT &= ~(1 << BUZZER_PIN);   // resetiraj pin zujalice
	}
	
}

bool filtered_pin_state(uint8_t _port, uint8_t _pin, bool _value, uint16_t T){
	// pokazivac na PIN registar porta _port
	volatile uint8_t* port = PIN[_port];
	// provjera da li je 90% vremena pin u vrijednosti _value
	if (get_pin(*port,_pin) == _value){
		uint16_t a = 0;
		uint16_t brojac = 0;
		while(a++ < T){
			_delay_ms(1);
			if (get_pin(*port,_pin) == _value) brojac++;
		}
		if (brojac >= T * 9 /10){
			return _value;
		}
	}
	return !_value;
}


// deklaracija i inicijalizacija varijabli koje se koriste za spremanje starog stanja
// PIN registra, a za potrebe funkcija koje testiraju padajuci i rastuci brid
uint8_t pin_old_state[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

bool isFalling_edge(uint8_t _port, uint8_t _pin) {
	// ako je novo filtrirano stanje pina false, a staro true => desio se padajuci brid
	if ((filtered_pin_state(_port,_pin, false, 25) == false) && (((pin_old_state[_port] & (1 << _pin)) >> _pin) == true)) {
		pin_old_state[_port] &= ~(1 << _pin);
		return true;
	}
	// ako nema brida, pohrani novu vrijednost pina u buducu staru vrijednost
	if (filtered_pin_state(_port,_pin, true, 25) == true) {
		pin_old_state[_port] |= (1 << _pin);
	}
	
	return false;
}


bool isRising_edge(uint8_t _port, uint8_t _pin) {
	// ako je novo filtrirano stanje pina true, a staro false => desio se rastuci brid	
	if ((filtered_pin_state(_port,_pin, true, 25) == true) && (((pin_old_state[_port] & (1 << _pin)) >> _pin) == false)) {
		pin_old_state[_port] |= (1 << _pin);
		return true;
	}
	// ako nema brida, pohrani novu vrijednost pina u buducu staru vrijednost
	if (filtered_pin_state(_port,_pin, false, 25) == false) {
		pin_old_state[_port] &= ~(1 << _pin);
	}
	
	return false;
}