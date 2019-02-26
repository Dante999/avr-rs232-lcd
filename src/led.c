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

#define LED_REG_PORT   PORTB
#define LED_REG_DDR    DDRB
#define LED_BIT        PB5


/**
 * @brief initializes the pin where the led is connected to
 */
void led_init() {
    LED_REG_DDR |= (1<<LED_BIT);
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
