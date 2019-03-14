#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "lcd.h"
#include "led.h"
#include "avr/interrupt.h"
#include "interpreter.h"
#include "timer0.h"

#define PRESCALER 64


/**
 * @brief initializes all modules
 */
void init() {

    led_init();
    uart_init();

    lcd_init(LCD_DISP_ON);
    lcd_clrscr();
}


/**
 * @brief the main function
 *
 * @return zero when exiting
 */
int main() {

    char uart_buffer[UART_BUFFER_SIZE] = "";

    init();

    uart_puts("init done!");
    lcd_puts("Ready!");

    sei();

    while(1) {

        if( uart_is_complete() ) {
            uart_read_buffer(uart_buffer);
            interprete(uart_buffer);
        }

    }

    return 0;
}
