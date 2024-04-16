#include <avr/io.h>
#include <util/delay.h>

#include "lcd_4bit.h"
#include "keypad_4x4.h"

int main(void) {

  // Setup

  lcd_init();
  lcd_set_cursor(0, 0);
  lcd_print_str("Enter password:");
  lcd_set_cursor(0, 1);
  lcd_print_str("----");
  lcd_set_cursor(0, 1);

  keypad_init();

  DDRC |= (1 << DDC4);
  DDRC |= (1 << DDC5);

  char password[] = {'3', '5', '9', '3'};
  char input[] = {'-', '-', '-', '-'};
  char key;
  int pos = 0;

  // Main loop

  while(1) {
    key = keypad_get_key();

    if (key == '#') {
      if (pos != 0) {
        pos--;
        input[pos] = '-';
        lcd_move_cursor_left();
        lcd_print_char('-');
        lcd_move_cursor_left();
      }    
    }
    else if (key == '*') {
      if (pos == 4) {
        lcd_clear();
        lcd_set_cursor(0, 0);

        if (password[0] == input[0] &&
            password[1] == input[1] &&
            password[2] == input[2] &&
            password[3] == input[3]) {
              PORTC |= (1 << PORTC5);
              lcd_print_str("Correct password");
              _delay_ms(3000);
              PORTC &= ~(1 << PORTC5);
        }
        else {
          PORTC |= (1 << PORTC4);
          lcd_print_str("Wrong password!");
          _delay_ms(3000);
          PORTC &= ~(1 << PORTC4);
        }

        for (int i = 0; i < 4; i++) {
          input[i] = '-';
        }

        lcd_clear();
        lcd_set_cursor(0, 0);
        lcd_print_str("Enter password:");
        lcd_set_cursor(0, 1);
        lcd_print_str("----");
        lcd_set_cursor(0, 1);
        pos = 0;
      }    
    }
    else if (key) {
      if (pos < 4) {
        input[pos] = key;
        pos++;
        lcd_print_char(key);
      }
    }
  }
}