/*******************************************************************************
 *
 * File    : led.c
 *
 * Author  : Dante999
 * Date    : 28.12.2018
 *
 * Tabsize : 8
 * License : GNU GPL v2
 *
 * turns the onboard led on, off or toggles it
 *
 *
 ******************************************************************************/


#include "led.h"
#include "timer0.h"
#include "timer2.h"
#include <avr/io.h>

#define LED_REG_PORT PORTB
#define LED_REG_DDR DDRB
#define LED_BIT PB5

/*******************************************************************************
 * initializes the module
 *
 * @param   none
 *
 * @return  none
 ******************************************************************************/
void led_init()
{
	timer0_init();
	timer2_init();

	LED_REG_DDR |= (1 << LED_BIT);

	led_green_pwm(0);
	led_yellow_pwm(0);
	led_red_pwm(0);
}

/*******************************************************************************
 * turns the onboard led on
 *
 * @param   none
 *
 * @return  none
 ******************************************************************************/
void led_on() { LED_REG_PORT |= (1 << LED_BIT); }

/*******************************************************************************
 * turns the onboard led off
 *
 * @param   none
 *
 * @return  none
 ******************************************************************************/
void led_off() { LED_REG_PORT &= ~(1 << LED_BIT); }

/*******************************************************************************
 * toggles the onboard led between on/off each function call
 *
 * @param   none
 *
 * @return  none
 ******************************************************************************/
void led_toggle() { LED_REG_PORT ^= (1 << LED_BIT); }

/*******************************************************************************
 * sets the pwm for the red led
 *
 * @param   power   brightness where 0 is off and 255 is max
 *
 * @return  none
 ******************************************************************************/
void led_red_pwm(uint8_t power) { timer0_pwmA(power); }

/*******************************************************************************
 * sets the pwm for the yellow led
 *
 * @param   power   brightness where 0 is off and 255 is max
 *
 * @return  none
 ******************************************************************************/
void led_yellow_pwm(uint8_t power) { timer0_pwmB(power); }

/*******************************************************************************
 * sets the pwm for the green led
 *
 * @param   power   brightness where 0 is off and 255 is max
 *
 * @return  none
 ******************************************************************************/
void led_green_pwm(uint8_t power) { timer2_pwmA(power); }
