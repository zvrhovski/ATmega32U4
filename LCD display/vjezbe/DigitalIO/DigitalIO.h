/*
 * DigitalIO.cpp
 *
 * Created: 4.1.2020. 19:26:41
 *  Author: Zoran
 */ 


class DigitalOutput {
	public:
	
	DigitalOutput() = default;
	DigitalOutput(uint8_t prt, uint8_t pn);
	DigitalOutput(uint8_t pn);
	
	void on() { *port |= (1 << pin_pos); }
	void off() { *port &= ~(1 << pin_pos); }
	void set() { *port |= (1 << pin_pos); }
	void reset() { *port &= ~(1 << pin_pos); }
	void toggle() { *port ^= (1 << pin_pos); }
	void disable() {*ddr &= ~(1 << pin_pos);}
	void enable() {*ddr |= (1 << pin_pos);}
	bool state() {return ((*port & (1 << pin_pos)) ? true : false); }
	
	private:
	volatile uint8_t *const port;
	volatile uint8_t *const ddr;
	uint8_t pin_pos;
};


class DigitalInput {
	public:
	
	DigitalInput() = default;
	DigitalInput(uint8_t prt, uint8_t pn);
	DigitalInput(uint8_t pn);

	void pullup_on() { *port |= (1 << pin_pos); }
	void pullup_off() { *port &= ~(1 << pin_pos); }
	bool state() {return ((*pin & (1 << pin_pos)) ? true : false); }
	bool isRising_edge();
	bool isFalling_edge();
	bool filtered_state(bool _value, uint16_t T);

	private:
	volatile uint8_t *const port;
	volatile uint8_t *const ddr;
	volatile uint8_t *const pin;
	uint8_t pin_pos;
	bool old_state;
};
