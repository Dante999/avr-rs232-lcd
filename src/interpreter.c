#include <avr/io.h>
#include <string.h>
#include "led.h"
#include "uart.h"
#include "lcd.h"
/**
 * commands:
 * -write (0|1) <string>
 * -clear (0|1)
 * -led (0|1)
**/

#define CMD_GOTOXY      "gotoxy"
#define CMD_CLEARSCREEN "clearscreen"
#define CMD_CLEARLINE   "clearline"
#define CMD_WRITE       "write"
#define CMD_LED         "led"



#define RESPONSE_OK "-> OK"

static uint8_t current_lcd_line = 0;



static int8_t char_to_int(char c) {

    if( '0' <= c && c <= '9' ) {
        return (c-'0');
    }
    else {
        return -1;
    }

}

static int8_t string_to_int(const char *s) {

    if( strlen(s) == 1 ) {
        return char_to_int(s[0]);
    }
    else {
        int8_t digit_10 = char_to_int(s[0]);
        int8_t digit_01 = char_to_int(s[1]);

        if( digit_10 > 0 && digit_01 > 0 ){
            return (10*digit_10) + digit_01;
        }
        else {
            return -1;
        }
    }

}

static uint8_t is_command(const char *buffer, const char *cmd) {

    if( strncmp(buffer, cmd, strlen(cmd)) == 0 ) {
        return 1;
    }
    else {
        return 0;
    }
}


/**
 * @brief handles the led command
 *
 * @param s     the user input
 */
static void handle_led(const char *s) {
    uint8_t value_index = strlen(CMD_LED)+1;

    if( s[value_index] == '0' ) {
        led_set_off();
    }
    else if( s[value_index] == '1'){
        led_set_on();
    }
    else {
        uart_puts(">invalid value: ");
        uart_putc(s[value_index]);
        uart_putsln("");
        return;
    }

    uart_putsln(RESPONSE_OK);
}


/**
 * @brief handles the clearscreen command
 */
static void handle_clearscreen(void) {
    lcd_clrscr();
    lcd_gotoxy(0,0);
    uart_putsln(RESPONSE_OK);
}

static void handle_clearline(void) {
    lcd_gotoxy(0, current_lcd_line);

    for( uint8_t i=0; i < LCD_DISP_LENGTH; i++) {
        lcd_putc(' ');
    }

    lcd_gotoxy(0, current_lcd_line);
    uart_putsln(RESPONSE_OK);

}


// goto 12 1
static void handle_gotoxy(const char *s) {

    char x_value[3] = "";
    char y_value[3] = "";

    char *p_xvalue = strchr(s, ' ')+1;
    char *p_yvalue = strchr(p_xvalue+1, ' ')+1;

    uint8_t length_xvalue = p_yvalue-p_xvalue-1;

    strncpy(x_value, p_xvalue, (length_xvalue));
    strncpy(y_value, p_yvalue, 2);

    x_value[2] = '\0';
    y_value[2] = '\0';


    int8_t x = string_to_int(x_value);
    int8_t y = string_to_int(y_value);

    lcd_gotoxy(x, y);
    current_lcd_line = y;

    uart_putsln(RESPONSE_OK);
}


static void handle_write(const char *s) {
    uint8_t index_content = strlen(CMD_WRITE)+1;

    const char *value = &s[index_content];

    lcd_puts(value);

    uart_putsln(RESPONSE_OK);
}


void interprete(const char *received_content) {


    if( is_command(received_content, CMD_LED) ) {
        handle_led(received_content);
    }
    else if( is_command(received_content, CMD_CLEARSCREEN)) {
        handle_clearscreen();
    }
    else if( is_command(received_content, CMD_GOTOXY)) {
        handle_gotoxy(received_content);
    }
    else if( is_command(received_content, CMD_CLEARLINE)) {
        handle_clearline();
    }
    else if( is_command(received_content, CMD_WRITE)) {
        handle_write(received_content);
    }
    else {
        uart_putsln("->unknown command!");
    }

}
