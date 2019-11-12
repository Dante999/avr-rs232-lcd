#include <avr/io.h>

#ifndef F_CPU
#	error F_CPU is not defined!
#endif

// 1, 8, 64, 256, 1024
#define PRESCALER 256

/*******************************************************************************
 * initializes the timer0 module
 *
 * @param   none
 *
 * @return  none
 ******************************************************************************/
void timer0_init()
{
	DDRD |= (1 << PD5) | (1 << PD6);

	TCCR0A |= (1 << WGM00); // PWM, phase correct, 8-bit
	TCCR0A |= (1 << COM0A1);
	TCCR0A |= (1 << COM0B1);

	OCR0A = 0;
	OCR0B = 0;

#if PRESCALER == 1
	TCCR1B |= (1 << CS00);
#elif PRESCALER == 8
	TCCR0B |= (1 << CS01);
#elif PRESCALER == 64
	TCCR0B |= (1 << CS01) | (1 << CS00);
#elif PRESCALER == 256
	TCCR0B |= (1 << CS02);
#elif PRESCALER == 1024
	TCCR0B |= (1 << CS02) | (1 << CS00);
#else
#	error invalid prescaler for timer0 selected!
#endif
}

/*******************************************************************************
 * sets the pwm value for output A
 *
 * @param   value   the pwm value [0-255]
 *
 * @return  none
 ******************************************************************************/
void timer0_pwmA(uint8_t value) { OCR0A = value; }

/*******************************************************************************
 * sets the pwm value for output B
 *
 * @param   value   the pwm value [0-255]
 *
 * @return  none
 ******************************************************************************/
void timer0_pwmB(uint8_t value) { OCR0B = value; }
