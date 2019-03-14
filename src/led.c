/*******************************************************************************
 *
 * File    : led.c
 *
 * Author  : Dante999
 * Date    : 28.12.2018
 *
 * Tabsize : 4
 * License : GNU GPL v2
 *
 * turns the onboard led on, off or toggles it
 *
 *
 ******************************************************************************/

#include <avr/io.h>
#include "led.h"
#include "timer0.h"
#include "timer2.h"

#define LED_REG_PORT   PORTB
#define LED_REG_DDR    DDRB
#define LED_BIT        PB5


/**
 * @brief initializes the pin where the led is connected to
 */
void led_init() {
    timer0_init();
    timer2_init();

    LED_REG_DDR |= (1<<LED_BIT);

    led_green_pwm(0);
    led_yellow_pwm(0);
    led_red_pwm(0);
}


/**
 * @brief turns the led on
 */
void led_set_on() {
    LED_REG_PORT |= (1<<LED_BIT);
}


/**
 * @brief turns the led off
 */
void led_set_off() {
    LED_REG_PORT &= ~(1<<LED_BIT);
}


/**
 * @brief toggles the led (on->off|off->on)
 */
void led_toggle() {
    LED_REG_PORT ^= (1<<LED_BIT);
}

void led_red_pwm(uint8_t power) {
    timer0_pwmA(power);
}

void led_yellow_pwm(uint8_t power) {
    timer0_pwmB(power);
}

void led_green_pwm(uint8_t power) {
    timer2_pwmA(power);
}
