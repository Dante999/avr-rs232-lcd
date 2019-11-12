#ifndef TIMER0_H
#define TIMER0_H

#include <avr/io.h>

void timer0_init();
void timer0_pwmA(uint8_t value);
void timer0_pwmB(uint8_t value);

#endif // TIMER0_H
