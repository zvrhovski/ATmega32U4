/*
 * avrvub.h
 *
 * Created: 4.1.2020. 12:46:12
 *  Author: Zoran Vrhovski
 */ 


#ifndef AVRVUB_H_
#define AVRVUB_H_


#ifndef F_CPU
# define F_CPU 16000000UL
#endif

#include <avr/io.h>

#ifndef MESSAGE_LENGTH
#define MESSAGE_LENGTH 50 // maksimalna duljina poruke
#endif


#if defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__)

#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7


#define B0 8
#define B1 9
#define B2 10
#define B3 11
#define B4 12
#define B5 13
#define B6 14
#define B7 15


#define C0 16
#define C1 17
#define C2 18
#define C3 19
#define C4 20
#define C5 21
#define C6 22
#define C7 23


#define D0 24
#define D1 25
#define D2 26
#define D3 27
#define D4 28
#define D5 29
#define D6 30
#define D7 31



volatile uint8_t *const PORT[4] = {&PORTA, &PORTB, &PORTC, &PORTD};
volatile uint8_t *const DDR[4] = {&DDRA, &DDRB, &DDRC, &DDRD};
volatile uint8_t *const PIN[4] = {&PINA, &PINB, &PINC, &PIND};

#define PA 0
#define PB 1
#define PC 2
#define PD 3

#endif

// definicija pinova za kontroler ATmega32u4

#if defined(__AVR_ATmega32U4__)
#define PB0 0
#define PB1 1
#define PB2 2
#define PB3 3
#define PB4 4
#define PB5 5
#define PB6 6
#define PB7 7

#define PC6 6
#define PC7 7

#define PD0 0
#define PD1 1
#define PD2 2
#define PD3 3
#define PD4 4
#define PD5 5
#define PD6 6
#define PD7 7

#define PE2 2
#define PE6 6

#define PF0 0
#define PF1 1
#define PF4 4
#define PF5 5
#define PF6 6
#define PF7 7

// definicija pinova za objektni pristup definiranje ulaza i izlaza
#define B0 8
#define B1 9
#define B2 10
#define B3 11
#define B4 12
#define B5 13
#define B6 14
#define B7 15

#define C6 22
#define C7 23

#define D0 24
#define D1 25
#define D2 26
#define D3 27
#define D4 28
#define D5 29
#define D6 30
#define D7 31

#define E2 34
#define E6 38

#define F0 40
#define F1 41
#define F4 44
#define F5 45
#define F6 46
#define F7 47

volatile uint8_t *const PORT[6] = {((volatile uint8_t *)0), &PORTB, &PORTC, &PORTD, &PORTE, &PORTF};
volatile uint8_t *const DDR[6] = {((volatile uint8_t *)0), &DDRB, &DDRC, &DDRD, &DDRE, &DDRF};
volatile uint8_t *const PIN[6] = {((volatile uint8_t *)0), &PINB, &PINC, &PIND, &PINE, &PINF};

// definicija konstanti za portove - oznake za portove
#define PA 0 // port A
#define PB 1 // port B
#define PC 2 // port C
#define PD 3 // port D
#define PE 4 // port E
#define PF 5 // port F

#endif


//manipulacija s ulazima i izlazima
#define set_port(port, position, _value)  (_value == true) ? (port |= (1 << position)) : (port &= ~(1 << position))
#define get_pin(port, position) ((port & (1 << position)) >> position)
#define toggle_port(port, position) port ^= (1 << position)


//postavljanje registra za ulazne i izlazne pinove
#define output_port(x,y) x |= (1 << y)
#define input_port(x,y) x &= ~(1 << y)

//postavljanje bita u 8-bitnoj maski
#define set_bit(bit) (1 << bit)
#define reset_bit(bit) ~(1 << bit)

//postavljanje bita u registru x na poziciji y 
#define set_bit_reg(x,y) x |= set_bit(y) // postavljanje u 1
#define reset_bit_reg(x,y) x &= reset_bit(y) // postavljanje u 0


// definiranje ina za zujalicu i funkcija BUZZ za zujanje
#define BUZZER_PORT PORTF
#define BUZZER_DDR  DDRF
#define BUZZER_PIN  PF4

void BUZZ(double duration, int freq);


bool filtered_pin_state(uint8_t _port, uint8_t _pin, bool _value, uint16_t T);

//#define filtered_pin_state(PINx, Px, pin_state, T) filter_pin(&(PINx), Px, pin_state, T)


bool isFalling_edge(uint8_t _port, uint8_t _pin);
bool isRising_edge(uint8_t _port, uint8_t _pin);

#endif /* AVRVUB_H_ */