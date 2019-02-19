#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "lcd.h"
#include "led.h"
#include "avr/interrupt.h"
#include "parser.h"



void init() {

    led_init();
    uart_init();
    lcd_init(LCD_DISP_ON);
    lcd_clrscr();

}




int main() {

    char uart_buffer[UART_BUFFER_SIZE] = "";

    init();



    uart_puts("init done!");

    lcd_gotoxy(0,0);
    lcd_puts("line 0: init done!");
    lcd_gotoxy(0,1);
    lcd_puts("line 1: init done!");

    sei();

    while(1) {

        if( uart_is_complete() ) {
            uart_read_buffer(uart_buffer);
            interprete(uart_buffer);
        }


//        led_set_on();
//        _delay_ms(1000);

//        led_set_off();
//        _delay_ms(1000);
    }
}
