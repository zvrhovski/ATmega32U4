/*
 * interrupt.h
 *
 * Created: 10.1.2020. 17:24:33
 *  Author: Zoran
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <avr/interrupt.h>

void interrupt_enable(){
	sei();
}

void interrupt_disable(){
	cli();
}	


/*******************************************************/
/*************************INT0**************************/

void int0_enable(){
	EIMSK |= (1 << INT0);
}

void int0_disable(){
	EIMSK &= ~(1 << INT0);
}

void int0_set_low_level(){
	EICRA &= ~((1 << ISC01) | (1 << ISC00));
	EICRA |= (0 << ISC01) | (0 << ISC00);
}

void int0_set_rising_falling_edge(){
	EICRA &= ~((1 << ISC01) | (1 << ISC00));
	EICRA |= (0 << ISC01) | (1 << ISC00);
}

void int0_set_falling_edge(){
	EICRA &= ~((1 << ISC01) | (1 << ISC00));
	EICRA |= (1 << ISC01) | (0 << ISC00);
}


void int0_set_rising_edge(){
	EICRA &= ~((1 << ISC01) | (1 << ISC00));
	EICRA |= (1 << ISC01) | (1 << ISC00);
}



/*******************************************************/
/*************************INT1**************************/

void int1_enable(){
	EIMSK |= (1 << INT1);
}

void int1_disable(){
	EIMSK &= ~(1 << INT1);
}

void int1_set_low_level(){
	EICRA &= ~((1 << ISC11) | (1 << ISC10));
	EICRA |= (0 << ISC11) | (0 << ISC10);
}

void int1_set_rising_falling_edge(){
	EICRA &= ~((1 << ISC11) | (1 << ISC10));
	EICRA |= (0 << ISC11) | (1 << ISC10);
}

void int1_set_falling_edge(){
	EICRA &= ~((1 << ISC11) | (1 << ISC10));
	EICRA |= (1 << ISC11) | (0 << ISC10);
}


void int1_set_rising_edge(){
	EICRA &= ~((1 << ISC11) | (1 << ISC10));
	EICRA |= (1 << ISC11) | (1 << ISC10);
}



/*******************************************************/
/*************************INT2**************************/


void int2_enable(){
	EIMSK |= (1 << INT2);
}

void int2_disable(){
	EIMSK &= ~(1 << INT2);
}


void int2_set_low_level(){
	EICRA &= ~((1 << ISC21) | (1 << ISC20));
	EICRA |= (0 << ISC21) | (0 << ISC20);
}

void int2_set_rising_falling_edge(){
	EICRA &= ~((1 << ISC21) | (1 << ISC20));
	EICRA |= (0 << ISC21) | (1 << ISC20);
}

void int2_set_falling_edge(){
	EICRA &= ~((1 << ISC21) | (1 << ISC20));
	EICRA |= (1 << ISC21) | (0 << ISC20);
}


void int2_set_rising_edge(){
	EICRA &= ~((1 << ISC21) | (1 << ISC20));
	EICRA |= (1 << ISC21) | (1 << ISC20);
}


/*******************************************************/
/*************************INT3**************************/


void int3_enable(){
	EIMSK |= (1 << INT3);
}

void int3_disable(){
	EIMSK &= ~(1 << INT3);
}

void int3_set_low_level(){
	EICRA &= ~((1 << ISC31) | (1 << ISC30));
	EICRA |= (0 << ISC31) | (0 << ISC30);
}

void int3_set_rising_falling_edge(){
	EICRA &= ~((1 << ISC31) | (1 << ISC30));
	EICRA |= (0 << ISC31) | (1 << ISC30);
}

void int3_set_falling_edge(){
	EICRA &= ~((1 << ISC31) | (1 << ISC30));
	EICRA |= (1 << ISC31) | (0 << ISC30);
}


void int3_set_rising_edge(){
	EICRA &= ~((1 << ISC31) | (1 << ISC30));
	EICRA |= (1 << ISC31) | (1 << ISC30);
}


/*******************************************************/
/*************************INT6**************************/

void int6_enable(){
	EIMSK |= (1 << INT6);
}

void int6_disable(){
	EIMSK &= ~(1 << INT6);
}


void int6_set_low_level(){
	EICRB &= ~((1 << ISC61) | (1 << ISC60));
	EICRB |= (0 << ISC61) | (0 << ISC60);
}

void int6_set_rising_falling_edge(){
	EICRB &= ~((1 << ISC61) | (1 << ISC60));
	EICRB |= (0 << ISC61) | (1 << ISC60);
}

void int6_set_falling_edge(){
	EICRB &= ~((1 << ISC61) | (1 << ISC60));
	EICRB |= (1 << ISC61) | (0 << ISC60);
}


void int6_set_rising_edge(){
	EICRB &= ~((1 << ISC61) | (1 << ISC60));
	EICRB |= (1 << ISC61) | (1 << ISC60);
}


// prekidna rutina za vanjski prekid INT0
ISR(INT0_vect){

}

// prekidna rutina za vanjski prekid INT1
ISR(INT1_vect){

}

// prekidna rutina za vanjski prekid INT2
ISR(INT2_vect){
	
}


// prekidna rutina za vanjski prekid INT3
ISR(INT3_vect){
	
}


// prekidna rutina za vanjski prekid INT6
ISR(INT6_vect){
	
}




#endif /* INTERRUPT_H_ */