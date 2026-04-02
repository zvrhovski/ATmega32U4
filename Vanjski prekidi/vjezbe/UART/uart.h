/*
 * uart.h
 *
 * Created: 6.1.2020. 17:50:13
 *  Author: Zoran
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "stdbool.h"
#include <stdio.h>

void uart_init(uint32_t baud_rate);
void uart_write_char(char ch);
void uart_print_string(char *str);
void uart_print(char *szFormat, ...);
char uart_read_char();
bool uart_read_all();

#define end_char '\r' // zakljucni znak // znak '\r' je Carriage Return (CR) ASCII kod 0x0D
#define MESSAGE_LENGTH 50 // maksimalna duljina poruke
char uart_buffer[MESSAGE_LENGTH + 1]; // spremnik za dolazne poruke
char *p_uart_buffer = uart_buffer; //pointer na buffer

void uart_init(uint32_t baud_rate) {
	
	uint16_t ubrr_value;
	ubrr_value = F_CPU / (16. * baud_rate) - 1;
	// konfiguracija baudrate - a
	UBRR1 = ubrr_value; 

	UCSR1C |= (1 << UCSZ10) | (1 << UCSZ11); // 8-bitna komunikacija
	UCSR1B |= (1 << RXEN1) | (1 << TXEN1); // Rx i Tx omogucen
	UCSR1B |= (1 << RXCIE1); // Prekid Rx omogucen
}


char uart_read_char() {
	//cekaj dok podatak ne bude dostupan
	while(!(UCSR1A & (1<<RXC1)));
	return UDR1;
}


void uart_write_char(char data) {
	//cekaj dok transmiter ne bude spreman za slanje
	while(!(UCSR1A & (1<<UDRE1)));
	UDR1 = data;
}


// prekidna rutina koja prima poruke i zapisuje ih u buffer
ISR(USART1_RX_vect) {
	
	*p_uart_buffer = uart_read_char();
	if (*p_uart_buffer != end_char)
	p_uart_buffer++;
}	


// vraca true kada je pristigla cijela poruka
bool uart_read_all() {

	if(*p_uart_buffer == end_char) {
		*p_uart_buffer = '\0';
		p_uart_buffer = uart_buffer;
		return true;
	}	
	else {
		return false;	
	}
}



void uart_print_string(char *str) {

	while(*str) {
		uart_write_char(*str);
		str++;
	}
}

void uart_print(char *szFormat, ...) {
	// kreiranje stringa
	char szBuffer[MESSAGE_LENGTH];
	va_list pArgs;
	va_start(pArgs, szFormat);
	vsprintf(szBuffer, szFormat, pArgs);
	va_end(pArgs);
	//posalji string
	uart_print_string(szBuffer);
}
