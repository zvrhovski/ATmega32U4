/*
 * ssd.h
 *
 * Created: 9.4.2020. 12:43:59
 *  Author: Zoran Vrhovski
 */ 
#ifndef SSD_H_
#define SSD_H_

//DDR registri za ulaze SI, SCK i RCK
#define SI_DDR DDRC
#define SCK_DDR DDRF
#define RCK_DDR DDRF

//PORT registri za ulaze SI, SCK i RCK
#define SI_PORT PORTC
#define SCK_PORT PORTF
#define RCK_PORT PORTF

//Pinovi za ulaze SI, SCK i RCK
#define SI_PIN PC7
#define SCK_PIN PF1
#define RCK_PIN PF0

#define DOT 0x01

#define NO_DOT 0x01
#define DOT_ 0x01


// specijalni znakovi
#define EMPTY_SPACE 0x00
#define MINUS 0x02
#define BIG_DEEGRE 0xC6

// neka slova
#define CHAR_A 0xEE
#define CHAR_b 0x3E
#define CHAR_C 0x9C
#define CHAR_d 0x7A
#define CHAR_E 0x9E
#define CHAR_F 0x8E
#define CHAR_H 0x6E
#define CHAR_I 0x0C
#define CHAR_P 0xCE
#define CHAR_U 0x7C
#define CHAR_S 0xB6
#define CHAR_Y 0x76

// brojevi
#define DIGIT_0 0xFC
#define DIGIT_1 0x60
#define DIGIT_2 0xDA
#define DIGIT_3 0xF2
#define DIGIT_4 0x66
#define DIGIT_5 0xB6
#define DIGIT_6 0xBE
#define DIGIT_7 0xE0
#define DIGIT_8 0xFE
#define DIGIT_9 0xF6


const uint8_t digits[10] = {
	
	/*0*/    0b11111100,
	/*1*/    0b01100000,
	/*2*/    0b11011010,
	/*3*/    0b11110010,
	/*4*/    0b01100110,
	/*5*/    0b10110110,
	/*6*/    0b10111110,
	/*7*/    0b11100000,
	/*8*/    0b11111110,
	/*9*/    0b11110110
};

void shift_bit_init(){
	SI_DDR |= (1 << SI_PIN);
	SCK_DDR |= (1 << SCK_PIN);
	RCK_DDR |= (1 << RCK_PIN);
}

void shift_bit_clock_sck(){
	// rastuci brid signala SCK
	set_port(SCK_PORT, SCK_PIN, 1); //SCK = 1
	_delay_us(1);
	set_port(SCK_PORT, SCK_PIN, 0); //SCK = 0
	_delay_us(1);
}

void shift_bit_clock_rck(){
	// rastuci brid signala RCK
	set_port(RCK_PORT, RCK_PIN, 1); //RCK = 1
	_delay_us(1);
	set_port(RCK_PORT, RCK_PIN, 0); //RCK = 0
	_delay_us(1);
}

void shift_bit_send_1byte(uint8_t number){
	for(int i = 0; i < 8; i++) {
		if(number & 0x01) { // ako je number LSB == 1
			set_port(SI_PORT, SI_PIN, 1); // na SI posalji 1
		}
		else { // ako je number LSB == 0
			set_port(SI_PORT, SI_PIN, 0); // na SI posalji 0
		}

		shift_bit_clock_sck();	
		number = number >> 1; // posmakni broj za jedan u desno
	}

}

void shift_bit_send_4byte(uint8_t num1, uint8_t num2, uint8_t num3, uint8_t num4){

	shift_bit_send_1byte(num1);
	shift_bit_send_1byte(num2);
	shift_bit_send_1byte(num3);
	shift_bit_send_1byte(num4);
	
	shift_bit_clock_rck();
}

#endif /* SSD_H_ */