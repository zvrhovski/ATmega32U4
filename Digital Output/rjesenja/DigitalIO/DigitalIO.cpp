/*
 * DigitalIO.cpp
 *
 * Created: 6.3.2020. 11:41:40
 *  Author: Zoran
 */ 

#include "../AVR VUB/avrvub.h"
#include "DigitalIO.h"
#include <util/delay.h>


inline uint8_t toPort(uint8_t pp) {return pp / 8;}
inline uint8_t toPin(uint8_t pp) {return pp % 8;}



// Class DigitalOutput
DigitalOutput::DigitalOutput(uint8_t prt, uint8_t pn) : port(PORT[prt]), ddr(DDR[prt]), pin_pos(pn) {
	*port &= ~(1 << pin_pos);
	*ddr |= (1 << pin_pos);
}


DigitalOutput::DigitalOutput(const uint8_t pn) : port(PORT[toPort(pn)]), ddr(DDR[toPort(pn)]), pin_pos(toPin(pn)) {
	*port &= ~(1 << pin_pos);
	*ddr |= (1 << pin_pos);
}


// Class DigitalInput
DigitalInput::DigitalInput(uint8_t prt, uint8_t pn) : port(PORT[prt]), ddr(DDR[prt]), pin(PIN[prt]), pin_pos(pn) {
	*port &= ~(1 << pin_pos);
	*ddr &= ~(1 << pin_pos);
	old_state = false;
}

DigitalInput::DigitalInput(const uint8_t pn) : port(PORT[toPort(pn)]), ddr(DDR[toPort(pn)]), pin(PIN[toPort(pn)]), pin_pos(toPin(pn)) {
	*port &= ~(1 << pin_pos);
	*ddr &= ~(1 << pin_pos);
	old_state = true;
}

bool DigitalInput::isRising_edge() {
	
	if ((state() == true) && (old_state == false)) {
		old_state = true;
		return true;
	}

	if (state() == false) {
		old_state = false;
	}
	
	return false;
}

bool DigitalInput::isFalling_edge() {
	
	if ((state() == false) && (old_state == true)) {
		old_state = false;
		return true;
	}

	if (state() == true) {
		old_state = true;
	}
	
	return false;
}

bool DigitalInput::filtered_state(bool _value, uint16_t T) {
	
	if (state() == _value){
		uint16_t a = 0;
		uint16_t brojac = 0;
		while(a++ < T){
			_delay_ms(1);
			if (state() == _value) brojac++;
		}
		if (brojac >= T * 9 /10){
			return _value;
		}
	}
	return !_value;
}