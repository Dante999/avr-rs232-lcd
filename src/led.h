#ifndef LED_H
#define LED_H

#include <avr/io.h>

void led_init();
void led_on();
void led_off();
void led_toggle();

void led_red_pwm(uint8_t power);
void led_yellow_pwm(uint8_t power);
void led_green_pwm(uint8_t power);

#endif // LED_H
