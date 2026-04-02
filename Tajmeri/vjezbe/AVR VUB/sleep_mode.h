/*
 * sleep_mode.h
 *
 * Created: 9.1.2020. 13:04:00
 *  Author: Zoran
 */ 


#ifndef SLEEP_MODE_H_
#define SLEEP_MODE_H_

#include <avr/sleep.h>

// definicija sleep modova, page 47 
#define SLEEP_MODE_IDLE				((0 << SM2) | (0 << SM1) | (0 << SM0))
#define SLEEP_MODE_NOISE_REDUCTION	((0 << SM2) | (0 << SM1) | (1 << SM0))
#define SLEEP_MODE_POWER_DOWN		((0 << SM2) | (1 << SM1) | (0 << SM0))
#define SLEEP_MODE_POWER_SAVE		((0 << SM2) | (1 << SM1) | (1 << SM0))
#define SLEEP_MODE_STANDBY			((1 << SM2) | (1 << SM1) | (0 << SM0))
#define SLEEP_MODE_EXT_STANDBY		((1 << SM2) | (1 << SM1) | (1 << SM0))	

void sleep_mode_enable(uint8_t mode){		
	SMCR |= mode | (1 << SE);
}

void sleep_mode_disable(){
	SMCR &= ~(1 << SE);
}

/* makronaredba kojom se CPU stavlja u sleep (pozivanje instrukcije SLEEP)
sleep_cpu();
*/


#endif /* SLEEP_MODE_H_ */