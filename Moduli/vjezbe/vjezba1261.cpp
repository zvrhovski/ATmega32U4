/*
 Naslov: MIKROUPRAVLJACI - Programiranje mikrokontrolera AVR familije
 Autor: Zoran Vrhovski
 
 Vježba 12.6.1
 */ 

#include <avr/io.h>
#include "AVR VUB/avrvub.h"
#include <util/delay.h>
#include "LCD/lcd.h"
#include "uart/uart.h"
#include "Interrupt/interrupt.h"
#include "Timer/timer.h"

void inicijalizacija() {
	
	lcd_init(); // konfiguracija LCD displeja
	uart_init(19200); // UART konfiguracija
	// tajmer 1 u Phase Correct nacinu rada 
	timer1_set_prescaler(TIMER1_PRESCALER_64);
	timer1_set_phase_correct_PWM_8bit();
	// neinvertirani PWM na kanalima OC1A, OC1B i OC1C
	timer1_OC1A_enable_non_inverted_PWM();
	timer1_OC1B_enable_non_inverted_PWM();
	timer1_OC1C_enable_non_inverted_PWM();
	// izlazni pinovi PB5 (R), PB6 (G), PB7 (B)	
	DDRB |= (1 << PB5) | (1 << PB6) | (1 << PB7);	
	interrupt_enable();
}

int main(void) {

	inicijalizacija();
	uint8_t RGB[3] = {0, 0, 0};
	
	while(1) {
		
		if(uart_read_all()) {
			lcd_clrscr();
			lcd_home();
			lcd_print("%s\n", uart_buffer);
			
			if(uart_buffer[0] == 'R') {	
				RGB[0] = 0;
				RGB[1] = 0;
				RGB[2] = 0;
				// Citanje poruke tipa R26;14;88*
				for(uint8_t i = 1, j = 0; uart_buffer[i] != '*'; i++) {
					if (uart_buffer[i] != ';') {
						RGB[j] = RGB[j] * 10  + (uart_buffer[i] - 48);
					}
					else {
						j++;
					}
				}
				//postavite sirine PWM impulsa na pinovima OC1A, OC1B i OC1C
				OC1A_set_duty_cycle(RGB[0], PWM_8BIT);
				OC1B_set_duty_cycle(RGB[1], PWM_8BIT);
				OC1C_set_duty_cycle(RGB[2], PWM_8BIT);
				// ispis pojedinih sirina impulsa
				lcd_print("%u %u %u *", RGB[0], RGB[1], RGB[2]);
			}
		}
	}
}