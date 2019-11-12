#include <avr/io.h>

#ifndef F_CPU
#	error F_CPU is not defined!
#endif

// 1, 8, 64, 256, 1024
#define PRESCALER 256

/*******************************************************************************
 * initializes the timer2 module
 *
 * @param   none
 *
 * @return  none
 ******************************************************************************/
void timer2_init()
{
	DDRB |= (1 << PB3);

	TCCR2A |= (1 << WGM20); // PWM, phase correct, 8-bit
	TCCR2A |= (1 << COM2A1);

	OCR2A = 0;

#if PRESCALER == 1
	TCCR2B |= (1 << CS20);
#elif PRESCALER == 8
	TCCR2B |= (1 << CS21);
#elif PRESCALER == 64
	TCCR2B |= (1 << CS21) | (1 << CS20);
#elif PRESCALER == 256
	TCCR2B |= (1 << CS22);
#elif PRESCALER == 1024
	TCCR2B |= (1 << CS22) | (1 << CS20);
#else
#	error invalid prescaler for timer2 selected!
#endif
}

/*******************************************************************************
 * sets the pwm value for output A
 *
 * @param   value   the pwm value [0-255]
 *
 * @return  none
 ******************************************************************************/
void timer2_pwmA(uint8_t value) { OCR2A = value; }
