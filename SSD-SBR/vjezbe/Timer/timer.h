/*
 * timer.h
 *
 * Created: 9.1.2020. 18:24:42
 *  Author: Zoran
 */ 


#ifndef TIMER_H_
#define TIMER_H_

float limit_duty (float duty) {
	if(duty > 100.0) {
		duty = 100.0;
	}
	if(duty < 0.0) {
		duty = 0.0;
	}
	return duty;
}

/*********************************************************/
/*************************TIMER0**************************/

//djelitelji frekvencije za timer0
#define TIMER0_PRESCALER_OFF		((0 << CS02) | (0 << CS01) | (0 << CS00))
#define TIMER0_PRESCALER_1			((0 << CS02) | (0 << CS01) | (1 << CS00))
#define TIMER0_PRESCALER_8			((0 << CS02) | (1 << CS01) | (0 << CS00))
#define TIMER0_PRESCALER_64			((0 << CS02) | (1 << CS01) | (1 << CS00))
#define TIMER0_PRESCALER_256		((1 << CS02) | (0 << CS01) | (0 << CS00))
#define TIMER0_PRESCALER_1024		((1 << CS02) | (0 << CS01) | (1 << CS00))
#define TIMER0_EXTERNAL_FALL_EDGE	((1 << CS02) | (1 << CS01) | (0 << CS00))
#define TIMER0_EXTERNAL_RISI_EDGE	((1 << CS02) | (1 << CS01) | (1 << CS00))

void timer0_set_prescaler(uint8_t prescaler){
	TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
	TCCR0B |= prescaler;
}

void timer0_interrupt_OVF_enable(){
	TIMSK0 |= (1 << TOIE0);
}

void timer0_interrupt_OVF_disable(){
	TIMSK0 &= ~(1 << TOIE0);
}

void timer0_set_normal_mode(){
	// ocistiti WGM0 bitove u registrima TCCR0 A i B
	TCCR0A &= ~((1 << WGM01) | (1 << WGM00));
	TCCR0B &= ~(1 << WGM02);
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR0A &= ~((1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0));
	// postaviti Normalna nacin rada
	TCCR0A |= (0 << WGM01) | (0 << WGM00);
	TCCR0B |= (0 << WGM02);
}

void timer0_set_fast_PWM(){
	// ocistiti WGM0 bitove u registrima TCCR0 A i B
	TCCR0A &= ~((1 << WGM01) | (1 << WGM00));
	TCCR0B &= ~(1 << WGM02);
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR0A &= ~((1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0));
	// postaviti Fast PWM nacin rada
	TCCR0A |= (1 << WGM01) | (1 << WGM00);
	TCCR0B |= (0 << WGM02);
}

void timer0_set_phase_correct_PWM(){
	// ocistiti WGM0 bitove u registrima TCCR0 A i B
	TCCR0A &= ~((1 << WGM01) | (1 << WGM00));
	TCCR0B &= ~(1 << WGM02);
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR0A &= ~((1 << COM0A1) | (1 << COM0A0) | (1 << COM0B1) | (1 << COM0B0));
	// postaviti Phase correct PWM nacin rada
	TCCR0A |= (0 << WGM01) | (1 << WGM00);
	TCCR0B |= (0 << WGM02);
}


void timer0_OC0A_enable_non_inverted_PWM(){
	TCCR0A &= ~((1 << COM0A1) | (1 << COM0A0));
	TCCR0A |= (1 << COM0A1) | (0 << COM0A0);
}

void timer0_OC0A_enable_inverted_PWM(){
	TCCR0A &= ~((1 << COM0A1) | (1 << COM0A0));
	TCCR0A |= (1 << COM0A1) | (1 << COM0A0);
}

void timer0_OC0A_disable(){
	TCCR0A &= ~((1 << COM0A1) | (1 << COM0A0));
}

void timer0_OC0B_enable_non_inverted_PWM(){
	TCCR0A &= ~((1 << COM0B1) | (1 << COM0B0));
	TCCR0A |= (1 << COM0B1) | (0 << COM0B0);
}

void timer0_OC0B_enable_inverted_PWM(){
	TCCR0A &= ~((1 << COM0B1) | (1 << COM0B0));
	TCCR0A |= (1 << COM0B1) | (1 << COM0B0);
}

void timer0_OC0B_disable(){
	TCCR0A &= ~((1 << COM0B1) | (1 << COM0B0));
}


void OC0A_set_duty_cycle(float duty){
	OCR0A = limit_duty(duty)*2.55;
}

void OC0B_set_duty_cycle(float duty){
	OCR0B = limit_duty(duty)*2.55;
}

/*********************************************************/
/*************************TIMER1**************************/

//djelitelji frekvencije za timer1
#define TIMER1_PRESCALER_OFF		((0 << CS12) | (0 << CS11) | (0 << CS10))
#define TIMER1_PRESCALER_1			((0 << CS12) | (0 << CS11) | (1 << CS10))
#define TIMER1_PRESCALER_8			((0 << CS12) | (1 << CS11) | (0 << CS10))
#define TIMER1_PRESCALER_64			((0 << CS12) | (1 << CS11) | (1 << CS10))
#define TIMER1_PRESCALER_256		((1 << CS12) | (0 << CS11) | (0 << CS10))
#define TIMER1_PRESCALER_1024		((1 << CS12) | (0 << CS11) | (1 << CS10))
#define TIMER1_EXTERNAL_FALL_EDGE	((1 << CS12) | (1 << CS11) | (0 << CS10))
#define TIMER1_EXTERNAL_RISI_EDGE	((1 << CS12) | (1 << CS11) | (1 << CS10))


//TOP vrijednost za PWM signale
#define PWM_8BIT 255
#define PWM_9BIT 511
#define PWM_10BIT 1023
#define PWM_ICR1 ICR1



void timer1_set_prescaler(uint8_t prescaler){
	TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
	TCCR1B |= prescaler;
}


void timer1_interrupt_OVF_enable(){
	TIMSK1 |= (1 << TOIE1);
}

void timer1_interrupt_OVF_disable(){
	TIMSK1 &= ~(1 << TOIE1);
}

void timer1_set_normal_mode(){
	// ocistiti WGM1 bitove u registrima TCCR1 A i B
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0) | (1 << COM1C1) | (1 << COM1C0));
	// postaviti Normalna nacin rada
	TCCR1A |= (0 << WGM11) | (0 << WGM10);
	TCCR1B |= (0 << WGM13) | (0 << WGM12);
}


void timer1_set_fast_PWM_8bit(){
	// ocistiti WGM1 bitove u registrima TCCR1 A i B
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0) | (1 << COM1C1) | (1 << COM1C0));
	// postaviti Fast PWM nacin rada - 8 bita [0, 255]
	TCCR1A |= (0 << WGM11) | (1 << WGM10);
	TCCR1B |= (0 << WGM13) | (1 << WGM12);
}

void timer1_set_fast_PWM_9bit(){
	// ocistiti WGM1 bitove u registrima TCCR1 A i B
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0) | (1 << COM1C1) | (1 << COM1C0));
	// postaviti Fast PWM nacin rada - 9 bita [0, 511]
	TCCR1A |= (0 << WGM11) | (1 << WGM10);
	TCCR1B |= (1 << WGM13) | (0 << WGM12);
}

void timer1_set_fast_PWM_10bit(){
	// ocistiti WGM1 bitove u registrima TCCR1 A i B
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0) | (1 << COM1C1) | (1 << COM1C0));
	// postaviti Fast PWM nacin rada - 10 bita [0, 1023]
	TCCR1A |= (0 << WGM11) | (1 << WGM10);
	TCCR1B |= (1 << WGM13) | (1 << WGM12);
}

void timer1_set_fast_PWM_ICR1(uint16_t top){
	// ocistiti WGM1 bitove u registrima TCCR1 A i B
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0) | (1 << COM1C1) | (1 << COM1C0));
	// postaviti Fast PWM nacin rada -  raspon brojanja [0, ICR1]
	TCCR1A |= (1 << WGM11) | (0 << WGM10);
	TCCR1B |= (1 << WGM13) | (1 << WGM12);
	ICR1 = top;
}


void timer1_set_phase_correct_PWM_8bit(){
	// ocistiti WGM1 bitove u registrima TCCR1 A i B
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0) | (1 << COM1C1) | (1 << COM1C0));
	// postaviti Phase correct PWM nacin rada - 8 bita [0, 255]
	TCCR1A |= (0 << WGM11) | (1 << WGM10);
	TCCR1B |= (0 << WGM13) | (0 << WGM12);
}

void timer1_set_phase_correct_PWM_9bit(){
	// ocistiti WGM1 bitove u registrima TCCR1 A i B
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0) | (1 << COM1C1) | (1 << COM1C0));
	// postaviti Phase correct PWM nacin rada - 9 bita [0, 511]
	TCCR1A |= (1 << WGM11) | (0 << WGM10);
	TCCR1B |= (0 << WGM13) | (0 << WGM12);
}

void timer1_set_phase_correct_PWM_10bit(){
	// ocistiti WGM1 bitove u registrima TCCR1 A i B
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0) | (1 << COM1C1) | (1 << COM1C0));
	// postaviti Phase correct PWM nacin rada - 10 bita [0, 1023]
	TCCR1A |= (1 << WGM11) | (1 << WGM10);
	TCCR1B |= (0 << WGM13) | (0 << WGM12);
}


void timer1_set_phase_correct_PWM_ICR1(uint16_t top){
	// ocistiti WGM1 bitove u registrima TCCR1 A i B
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0) | (1 << COM1C1) | (1 << COM1C0));
	// postaviti Phase correct PWM nacin rada - raspon brojanja [0, ICR1]
	TCCR1A |= (1 << WGM11) | (0 << WGM10);
	TCCR1B |= (1 << WGM13) | (0 << WGM12);
	ICR1 = top;
}

void timer1_OC1A_enable_non_inverted_PWM(){
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0));
	TCCR1A |= (1 << COM1A1) | (0 << COM1A0);
}

void timer1_OC1A_enable_inverted_PWM(){
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0));
	TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
}

void timer1_OC1A_disable(){
	TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0));
}

void timer1_OC1B_enable_non_inverted_PWM(){
	TCCR1A &= ~((1 << COM1B1) | (1 << COM1B0));
	TCCR1A |= (1 << COM1B1) | (0 << COM1B0);
}

void timer1_OC1B_enable_inverted_PWM(){
	TCCR1A &= ~((1 << COM1B1) | (1 << COM1B0));
	TCCR1A |= (1 << COM1B1) | (1 << COM1B0);
}

void timer1_OC1B_disable(){
	TCCR1A &= ~((1 << COM1B1) | (1 << COM1B0));
}

void timer1_OC1C_enable_non_inverted_PWM(){
	TCCR1A &= ~((1 << COM1C1) | (1 << COM1C0));
	TCCR1A |= (1 << COM1C1) | (0 << COM1C0);
}

void timer1_OC1C_enable_inverted_PWM(){
	TCCR1A &= ~((1 << COM1C1) | (1 << COM1C0));
	TCCR1A |= (1 << COM1C1) | (1 << COM1C0);
}

void timer1_OC1C_disable(){
	TCCR1A &= ~((1 << COM1C1) | (1 << COM1C0));
}

void OC1A_set_duty_cycle(float duty, uint16_t top){
	OCR1A = limit_duty(duty)*top/100.0;
}

void OC1B_set_duty_cycle(float duty, uint16_t top){
	OCR1B = limit_duty(duty)*top/100.0;
}

void OC1C_set_duty_cycle(float duty, uint16_t top){
	OCR1C = limit_duty(duty)*top/100.0;
}

/*********************************************************/
/*************************TIMER3**************************/

//djelitelji frekvencije za timer3
#define TIMER3_PRESCALER_OFF		((0 << CS32) | (0 << CS31) | (0 << CS30))
#define TIMER3_PRESCALER_1			((0 << CS32) | (0 << CS31) | (1 << CS30))
#define TIMER3_PRESCALER_8			((0 << CS32) | (1 << CS31) | (0 << CS30))
#define TIMER3_PRESCALER_64			((0 << CS32) | (1 << CS31) | (1 << CS30))
#define TIMER3_PRESCALER_256		((1 << CS32) | (0 << CS31) | (0 << CS30))
#define TIMER3_PRESCALER_1024		((1 << CS32) | (0 << CS31) | (1 << CS30))
#define TIMER3_EXTERNAL_FALL_EDGE	((1 << CS32) | (1 << CS31) | (0 << CS30))
#define TIMER3_EXTERNAL_RISI_EDGE	((1 << CS32) | (1 << CS31) | (1 << CS30))

void timer3_interrupt_OVF_enable(){
	TIMSK3 |= (1 << TOIE3);
}

void timer3_interrupt_OVF_disable(){
	TIMSK3 &= ~(1 << TOIE3);
}


void timer3_set_prescaler(uint8_t prescaler){
	TCCR3B &= ~((1 << CS32) | (1 << CS31) | (1 << CS30));
	TCCR3B |= prescaler;
}

void timer3_set_normal_mode(){
	// ocistiti WGM3 bitove u registrima TCCR3 A i B
	TCCR3A &= ~((1 << WGM31) | (1 << WGM30));
	TCCR3B &= ~((1 << WGM33) | (1 << WGM32));
	// ocistiti bitove za Output compare mode - iskljucenje genereriranja valnog oblika na odredjenom pinu
	TCCR3A &= ~((1 << COM3A1) | (1 << COM3A0) | (1 << COM3B1) | (1 << COM3B0) | (1 << COM3C1) | (1 << COM3C0));
	// postaviti Normalna nacin rada
	TCCR3A |= (0 << WGM31) | (0 << WGM30);
	TCCR3B |= (0 << WGM33) | (0 << WGM32);
}

// timer 3 ima Fast PWM, Phase Corect PWM itd., no generira PWM samo na pinu OC3A zbog cega nisu definirane funkcije za parametriranje
// PWM nacina rada kao u slucaju timer 0 i 1

/*
// prekidna rutina za Timer0
ISR(TIMER0_OVF_vect){
	TCNT0 = 0;
}

// prekidna rutina za Timer1
ISR(TIMER1_OVF_vect){
	TCNT1 = 0;
}

// prekidna rutina za Timer3
ISR(TIMER3_OVF_vect){
	TCNT3 = 0;
}
*/

#endif /* TIMER_H_ */