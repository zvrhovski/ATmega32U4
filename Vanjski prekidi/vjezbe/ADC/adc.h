/*
 * adc.h
 *
 * Created: 8.1.2020. 11:24:09
 *  Author: Zoran
 */ 


#ifndef ADC_H_
#define ADC_H_

// definirani djelitelji frekvencije
#define ADC_PRESCALE_DIV2		((0 << ADPS2) | (0 << ADPS1) | (1 << ADPS0))	// F_CPU/2
#define ADC_PRESCALE_DIV4		((0 << ADPS2) | (0 << ADPS1) | (0 << ADPS0))	// F_CPU/4
#define ADC_PRESCALE_DIV8		((0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))	// F_CPU/8
#define ADC_PRESCALE_DIV16		((1 << ADPS2) | (0 << ADPS1) | (0 << ADPS0))	// F_CPU/16
#define ADC_PRESCALE_DIV32		((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))	// F_CPU/32
#define ADC_PRESCALE_DIV64		((1 << ADPS2) | (0 << ADPS1) | (0 << ADPS0))	// F_CPU/64
#define ADC_PRESCALE_DIV128		((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))	// F_CPU/128
// odabir djelitelja frkevencije
#define ADC_PRESCALE			ADC_PRESCALE_DIV128

// do not change the mask value
#define ADC_PRESCALE_MASK		((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))


// definirane konstante za odabir referentnog iznosa napona
#define ADC_REFERENCE_AREF		((0 << REFS1) | (0 << REFS0))	// AREF pin
#define ADC_REFERENCE_AVCC		((0 << REFS1) | (1 << REFS0))	// AVCC pin
#define ADC_REFERENCE_RSVD		((1 << REFS1) | (0 << REFS0))	// Rezervirana
#define ADC_REFERENCE_256V		((1 << REFS1) | (1 << REFS0))	// REF je unutatnjih 2.56 V

// odabir referentnog iznosa napona od prethodnih tri mogu?ih
#define ADC_REFERENCE			ADC_REFERENCE_AVCC

// do not change the mask value
#define ADC_REFERENCE_MASK		((1 << REFS1) | (1 << REFS0))

// bit mask for adc channel multiplexer
#define ADC_MUX_MASK1			((1 << MUX4) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0))
#define ADC_MUX_MASK2			(1 << MUX5)


// channel defines (for reference and use in code)
// these channels supported by all AVRs with adc



#define ADC0			0x00
#define ADC1			0x01
#define ADC4			0x04
#define ADC5			0x05
#define ADC6			0x06
#define ADC7			0x07

#define ADC8			0x20
#define ADC9			0x21
#define ADC10			0x22
#define ADC11			0x23
#define ADC12			0x24
#define ADC13			0x25
#define ADCTEMP			0x27


// function prototypes

//! Initializes the A/D converter.
/// Turns ADC on and prepares it for use.
void adc_init(void);

//! Starts a conversion on A/D channel# ch,
/// returns the 10-bit value of the conversion when it is finished.
uint16_t adc_read(uint8_t ch);



#endif /* ADC_H_ */