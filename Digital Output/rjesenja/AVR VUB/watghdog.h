/*
 * watghdog.h
 *
 * Created: 9.1.2020. 09:47:04
 *  Author: Zoran
 */ 


#ifndef WATGHDOG_H_
#define WATGHDOG_H_

#include <avr/wdt.h>

// definicije vremena za watchdog - registar WDTCSR
#define WATCHDOG_TIME_15MS		 ((0 << WDP2) | (0 << WDP1) | (0 << WDP0))  
#define WATCHDOG_TIME_30MS		 ((0 << WDP2) | (0 << WDP1) | (1 << WDP0))
#define WATCHDOG_TIME_60MS		 ((0 << WDP2) | (1 << WDP1) | (0 << WDP0))
#define WATCHDOG_TIME_120MS		 ((0 << WDP2) | (1 << WDP1) | (1 << WDP0))
#define WATCHDOG_TIME_250MS		 ((1 << WDP2) | (0 << WDP1) | (0 << WDP0))
#define WATCHDOG_TIME_500MS		 ((1 << WDP2) | (0 << WDP1) | (1 << WDP0))
#define WATCHDOG_TIME_1S		 ((1 << WDP2) | (1 << WDP1) | (0 << WDP0))
#define WATCHDOG_TIME_2S		 ((1 << WDP2) | (1 << WDP1) | (1 << WDP0))


void watchdog_off(){
			
	// Disable all interrupts
	interrupt_disable();

	wdt_reset();
	/* Clear MCU Status Register. Not really needed here as we don't need to know why the MCU got reset. page 44 of datasheet */
	MCUSR &= ~(1<<WDRF);

	/* Disable and clear all Watchdog settings. Nice to get a clean slate when dealing with interrupts */

	WDTCSR |= (1<<WDCE) | (1<<WDE);
	/* Turn off WDT */
	WDTCSR = 0x00;

	interrupt_enable();
}


void watchdog_system_reset_on(uint8_t watchdog_time){
	
	interrupt_disable();
	
	wdt_reset();
	// Setup Watchdog for system reset and not interrupt
	WDTCSR |= (1<<WDCE) | (1<<WDE);

	// Set new prescaler (time-out) 	
	WDTCSR = (1<<WDE) | watchdog_time;

	// Enable all interrupts.
	interrupt_enable();	
}


void watchdog_interrupt_and_system_reset_on(uint8_t watchdog_time){
	
	interrupt_disable();

	// Setup Watchdog for system reset and interrupt
	WDTCSR |= (1<<WDCE) | (1<<WDE);

	// Set new prescaler (time-out)
	WDTCSR = (1<<WDE) | (1<<WDIE) | watchdog_time;

	// Enable all interrupts.
	interrupt_enable();
}


void watchdog_interrupt_on(uint8_t watchdog_time){
	
	interrupt_disable();

	// Setup Watchdog for interrupt and not system reset
	WDTCSR |= (1<<WDCE) | (1<<WDE);

	// Set new prescaler (time-out)
	WDTCSR = (1<<WDIE) | watchdog_time;

	// Enable all interrupts.
	interrupt_enable();
}

// interrupt rutina za Wathdog 
ISR(WDT_vect){
	
	lcd_print("WDT");	
}

#endif /* WATGHDOG_H_ */