#include <avr/io.h>
#include "led.h"

#define LED_REG_PORT   PORTB
#define LED_REG_DDR    DDRB
#define LED_BIT        PB5


void led_init() {
    LED_REG_DDR |= (1<<LED_BIT);
}

void led_set_on() {
    LED_REG_PORT |= (1<<LED_BIT);
}

void led_set_off() {
    LED_REG_PORT &= ~(1<<LED_BIT);
}

void led_toggle() {
    LED_REG_PORT ^= (1<<LED_BIT);
}
