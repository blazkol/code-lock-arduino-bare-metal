#include <avr/io.h>
#include <util/delay.h>

#include "lcd_4bit.h"
#include "keypad_4x4.h"

int main(void) {

  // Setup

  lcd_init();
  lcd_set_cursor(0, 0);
  lcd_print("Enter password:");
  lcd_set_cursor(0, 1);
  lcd_print("----");
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
    if (pos == 4) {
      if (password[0] == input[0] &&
          password[1] == input[1] &&
          password[2] == input[2] &&
          password[3] == input[3]) {
            PORTC |= (1 << PORTC5);
            _delay_ms(3000);
            PORTC &= ~(1 << PORTC5);
      }
      else {
        PORTC |= (1 << PORTC4);
        _delay_ms(3000);
        PORTC &= ~(1 << PORTC4);
      }
      pos = 0;
    }

    key = keypad_get_key();
    if (key) {
      input[pos] = key;
      pos++;
    }
  }
}