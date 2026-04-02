/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 10.1.5
 */ 

#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
#include "LCD/lcd.h"
#include "UART/uart.h"
#include "Interrupt/interrupt.h"
#include "DigitalIO/DigitalIO.h"
#include "Timer/timer.h"
#include "ADC/adc.h"

bool send_uart = false;
uint8_t send_uart_state = 0;
uint32_t vrijeme_16 = 0;

ISR(TIMER1_OVF_vect){
	TCNT1 = 49911;
	vrijeme_16++; // uvecaj svakih 1/16 s
	send_uart_state++; // korak [0,1,2,3,...]
	send_uart = true; // zahtjev za obradom svakih 1/16 s
}

void inicijalizacija() {
	uart_init(19200); //inicijalizacija serijske komunikacije
	lcd_init(); // konfiguriranje LCD displeja
	adc_init(); // konfiguriranje AD pretvorbe
	interrupt_enable(); //omoguci globalni prekid
	// konfiguriranje tajmera 1
	timer1_set_normal_mode();
	timer1_set_prescaler(TIMER1_PRESCALER_64);
	timer1_interrupt_OVF_enable();
	TCNT1 = 49911;
}

int main(void) {
	
	inicijalizacija();
	// stvaranje objekata za LED diode
	DigitalOutput LED_crvena(B4); // pin PB4 - crvena dioda
	DigitalOutput LED_zuta(B5); // pin PB5 - zuta dioda
	DigitalOutput LED_zelena(B6); // pin PB6 - zelena dioda
	DigitalOutput LED_plava(B7); // pin PB7 - plava dioda
	DigitalInput Tipkalo_D0(D0); // pin PD0 - tipkalo
	Tipkalo_D0.pullup_on(); // ukljuci pull up na PD0
	DigitalInput Tipkalo_D1(D1); // pin PD1 - tipkalo
	Tipkalo_D1.pullup_on(); // ukljuci pull up na PD1
	DigitalInput Tipkalo_F6(F6); // pin PF6 - tipkalo
	Tipkalo_F6.pullup_on(); // ukljuci pull up na PF6
	DigitalInput Tipkalo_F7(F7); // pin PF7 - tipkalo
	Tipkalo_F7.pullup_on(); // ukljuci pull up na PF6	
	char B, x, y; // za provjeru primljenih poruka
	uint16_t ADC_4, ADC_5; // vrijednost AD pretvorbe na pinu ADC4 i ADC5
	uint16_t ADC_4_s, ADC_5_s; // skalirani ADC4 i ADC5 na [0, 100]
	uint16_t vrijeme = 0;
	uint8_t vrijeme_m = 0;
	
	while(1) {
		// provjera primljenih poruka
		if(uart_read_all() == true) {
			lcd_clrscr();
			lcd_home();
			lcd_print("%s", uart_buffer);
			B = uart_buffer[0];
			x = uart_buffer[1];
			y = uart_buffer[2];
			// provjera prvog znaka
			if (B == 'B') {
				// automat stanja koji obraduje ostatak poruke tipa "xy"
				switch(x) {
					case '4':
					if (y == '1') LED_crvena.on();
					if (y == '0') LED_crvena.off();
					break;
					case '5':
					if (y == '1') LED_zuta.on();
					if (y == '0') LED_zuta.off();
					break;
					case '6':
					if (y == '1') LED_zelena.on();
					if (y == '0') LED_zelena.off();
					break;
					case '7':
					if (y == '1') LED_plava.on();
					if (y == '0') LED_plava.off();
					break;
					default:
					break;
				}
			}
		}
		
		ADC_4 = adc_read(ADC4);
		ADC_4_s = ADC_4 / 10.23; // ADC_4 skaliran na [0, 100]
		ADC_5 = adc_read(ADC5);
		ADC_5_s = ADC_5 / 10.23; // ADC_5 skaliran na [0, 100]
		vrijeme = vrijeme_16 / 16; //vrijeme u [s]
		vrijeme_m = vrijeme % 101; // vrijeme modul na [0,100]
				
		// if koji se obraduje svakih 1000/16 = 62.5 ms
		if (send_uart) {
			
			// t1 = 62.5 ms
			if (send_uart_state == 1) {
				uart_print("A;%u;%u;%u*\r", ADC_4_s, ADC_5_s, vrijeme_m);
			}
			// t3 = 187.5 ms
			if (send_uart_state == 3) {
				uart_print("P;%u;%u;%u;%u;%u;%u*\r", 1, 4, 5, vrijeme, ADC_4, ADC_5);
			}
			// if koji se obraduje na svaki paran poziv prekidne rutine (svakih 125 ms)
			if ((send_uart_state % 2) == 0) {
				// na padajuci brid tipkala PD0 (kada se tipkalo pritisne)
				if (Tipkalo_D0.isFalling_edge() == true) {
					if (LED_crvena.state()) {
						uart_print("B40*\r"); // posalji niz za crvena off
						LED_crvena.off();
					}
					else {
						uart_print("B41*\r"); // posalji niz za crvena on
						LED_crvena.on();
					}
			
				}
				// na padajuci brid tipkala PD1 (kada se tipkalo pritisne)			
				if (Tipkalo_D1.isFalling_edge() == true) {
					if (LED_zuta.state()) {
						uart_print("B50*\r"); // posalji niz za zuta off
						LED_zuta.off();
					}
					else {
						uart_print("B51*\r"); // posalji niz za zuta on
						LED_zuta.on();
					}
				}
				// na padajuci brid tipkala PF6 (kada se tipkalo pritisne)			
				if (Tipkalo_F6.isFalling_edge() == true) {
					if (LED_zelena.state()) {
						uart_print("B60*\r"); // posalji niz za zelena off
						LED_zelena.off();
					}
					else {
						uart_print("B61*\r"); // posalji niz za zelena on
						LED_zelena.on();
					}				
				}	
				// na padajuci brid tipkala PF7 (kada se tipkalo pritisne)
				if (Tipkalo_F7.isFalling_edge() == true) {
					if (LED_plava.state()) {
						uart_print("B70*\r"); // posalji niz za plava off
						LED_plava.off();
					}
					else {
						uart_print("B71*\r"); // posalji niz za plava on
						LED_plava.on();
					}
				}					
			}
			// kada prodje 16 * 1000/16 = 1000 ms, brojac koraka se postavlja na 0
			if (send_uart_state == 16) {
				send_uart_state = 0;
			}
			
			send_uart = false; // obraden if koji se obraduje svakih 1000/16 = 62.5 ms
		}
	}
	return 0;
}
