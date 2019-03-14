/*******************************************************************************
 *
 * File    : interpreter.c
 *
 * Author  : Dante999
 * Date    : 26.02.2019
 *
 * Tabsize : 4
 * License : GNU GPL v2
 *
 * this module interprets commands which were entered through the uart from the
 * user
 *
 ******************************************************************************/
#include <avr/io.h>
#include <string.h>
#include "led.h"
#include "uart.h"
#include "lcd.h"


#define CMD_GOTOXY      "gotoxy"
#define CMD_CLEARSCREEN "clearscreen"
#define CMD_CLEARLINE   "clearline"
#define CMD_WRITE       "write"
#define CMD_LED         "led"
#define CMD_HELP        "help"



static uint8_t current_lcd_line = 0;


/**
 * @brief indicates the user that the entered command was ok
 */
static void response_ok() {
    uart_putsln("-> OK");
}

/**
 * @brief inidcates the user that the entered command was not correct
 *
 * @param s     additional information what went wrong during execution
 */
static void response_error(char *s) {
    uart_puts("-> ERROR: ");
    uart_putsln(s);
}


/**
 * @brief converts a ascii-char digit to an integer
 *
 * @param c     the digit as ascii
 *
 * @return the digit as integer
 */
static int8_t char_to_int(char c) {

    if( '0' <= c && c <= '9' ) {
        return (c-'0');
    }
    else {
        return -1;
    }

}


/**
 * @brief converts a positive 2-digit-number from string to integer
 *
 * @param s     the 2-digit-number as string
 *
 * @return if the conversion succeed, a positive number or zero, otherwise -1
 */
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


/**
 * @brief checks if the given content starts with the given command
 *
 * @param content   the content which needs to be checked
 * @param cmd       the expected command which is at the beginning
 *
 * @return 1 -> the content starts with the given commmand
 *         0 -> the content does not start with the given command
 */
static uint8_t starts_with_command(const char *content, const char *cmd) {

    if( strncmp(content, cmd, strlen(cmd)) == 0 ) {
        return 1;
    }
    else {
        return 0;
    }
}




static int8_t stoui(const char *s, uint8_t *i) {

    int8_t digits[3];
    size_t len = strlen(s);

    if( len == 1 ) {
        digits[2] = 0;
        digits[1] = 0;
        digits[0] = char_to_int(s[0]);
    }
    else if( len == 2 ) {
        digits[2] = 0;
        digits[1] = char_to_int(s[0]);
        digits[0] = char_to_int(s[1]);
    }
    else if( len == 3 ) {
        digits[2] = char_to_int(s[0]);
        digits[1] = char_to_int(s[1]);
        digits[0] = char_to_int(s[2]);
    }
    else {
        return -2;
    }


    if( digits[0] < 0 || 9 < digits[0] ||
        digits[1] < 0 || 9 < digits[1] ||
        digits[2] < 0 || 2 < digits[2] ) {
        return -1;
    }
    else {

        *i  = digits[0] * 1;
        *i += digits[1] * 10;
        *i += digits[2] * 100;

        return 0;
    }
}

/**
 * @brief handles the led command
 *
 * @param s     the complete entered user input
 */
static void handle_led(const char *s) {

    char color[10];
    char value[4];

    memset(color, '\0', sizeof(color)/sizeof(color[0]));
    memset(value, '\0', sizeof(value)/sizeof(value[0]));

    char *pcolor = strchr(s,      ' ')+1;
    char *pvalue = strchr(pcolor, ' ')+1;

    strncpy(color, pcolor, (pvalue-pcolor)-1);
    strncpy(value, pvalue, 3);


    uint8_t pwm = 0;

    if( stoui(value, &pwm) != 0 ) {
        response_error("unknown value!");
        return;
    }

    if( strcmp(color, "green") == 0) {
        led_green_pwm(pwm);
    }
    else if( strcmp(color, "yellow") == 0 ) {
        led_yellow_pwm(pwm);
    }
    else if( strcmp(color, "red") == 0 ) {
        led_red_pwm(pwm);
    }
    else {
        response_error("unknown color!");
        return;
    }

    response_ok();
}


/**
 * @brief handles the clearscreen command
 */
static void handle_clearscreen(void) {
    lcd_clrscr();
    lcd_gotoxy(0,0);
    response_ok();
}


/**
 * @brief handles the clearline command
 */
static void handle_clearline(void) {
    lcd_gotoxy(0, current_lcd_line);

    for( uint8_t i=0; i < LCD_DISP_LENGTH; i++) {
        lcd_putc(' ');
    }

    lcd_gotoxy(0, current_lcd_line);

    response_ok();
}


/**
 * @brief handles the gotoxy command
 *
 * @param s     the complete entered user input
 */
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

    response_ok();
}


/**
 * @brief handle the write to lcd command
 *
 * @param s     the complete entered user input
 */
static void handle_write(const char *s) {
    uint8_t index_content = strlen(CMD_WRITE)+1;

    const char *value = &s[index_content];

    lcd_puts(value);

    response_ok();
}


/**
 * @brief handles the help command
 */
static void handle_help(void) {
    uart_putsln("List of available commands");
    uart_putsln("--------------------------");
    uart_putsln("help                  prints this help screen");
    uart_putsln("led <color> <0-255>   sets the brightness of the given");
    uart_putsln("                      led color (red|yellow|green)");
    uart_putsln("clearscreen           clears the complete lcd");
    uart_putsln("gotoxy <0-15> <0-1>   go's to the given coordinates on the lcd");
    uart_putsln("clearline             clears the current line where the cursor is located");
    uart_putsln("write <content>       writes the given content to the current position");
    uart_putsln("--------------------------");
}


/**
 * @brief interpretes the user input and decides what to do
 *
 * @param content   the complete content what the user has entered
 */
void interprete(const char *content) {

    if( starts_with_command(content, CMD_HELP) ) {
        handle_help();
    }
    else if( starts_with_command(content, CMD_LED) ) {
        handle_led(content);
    }
    else if( starts_with_command(content, CMD_CLEARSCREEN)) {
        handle_clearscreen();
    }
    else if( starts_with_command(content, CMD_GOTOXY)) {
        handle_gotoxy(content);
    }
    else if( starts_with_command(content, CMD_CLEARLINE)) {
        handle_clearline();
    }
    else if( starts_with_command(content, CMD_WRITE)) {
        handle_write(content);
    }
    else {
        response_error("unkown command! type help to see a list of commands!");
    }

}
