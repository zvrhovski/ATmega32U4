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

Shift_Bit_Register::Shift_Bit_Register(uint8_t pn_SI, uint8_t pn_SCK, uint8_t pn_RCK) : SI(pn_SI), SCK(pn_SCK), RCK(pn_RCK) {
		
}

void Shift_Bit_Register::send_1byte(uint8_t number) {

	for (int i = 0; i < 8; i++) {
		if(number & 0x01) { // ako je bit0 == 1
			SI.set(); // na SI posalji 1
		}
		else { // ako je bit0 == 0
			SI.reset(); // na SI posalji 0
		}
		
		clock_sck();					
		number = number >> 1; // posmakni broj za jedan u desno
	}
}



void Shift_Bit_Register::send_4byte(uint8_t num1, uint8_t num2, uint8_t num3, uint8_t num4){
	
	send_1byte(num1);
	send_1byte(num2);
	send_1byte(num3);
	send_1byte(num4);
	
	clock_rck();
}

void Shift_Bit_Register::clock_sck(){
	// rastuci brid signala SCK
	SCK.set(); //SCK = 1
	_delay_us(1);
	SCK.reset(); //SCK = 0
	_delay_us(1);
}


void Shift_Bit_Register::clock_rck(){
	// rastuci brid signala RCK
	RCK.set(); //RCK = 1
	_delay_us(1);
	RCK.reset(); //RCK = 0
	_delay_us(1);
}
