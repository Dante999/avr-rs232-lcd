#ifndef LED_H
#define LED_H

extern void led_init();
extern void led_set_on();
extern void led_set_off();
extern void led_toggle();

extern void led_red_pwm(uint8_t power);
extern void led_yellow_pwm(uint8_t power);
extern void led_green_pwm(uint8_t power);

#endif // LED_H
