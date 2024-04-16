#include <avr/io.h>
#include <util/delay.h>

#include "lcd_4bit.h"

void lcd_nibble(unsigned char input_nibble) {
  if (input_nibble & (1<<0)) LCD_D4_PORT |= (1<<LCD_D4);
  else LCD_D4_PORT &= ~(1<<LCD_D4);
  
  if (input_nibble & (1<<1)) LCD_D5_PORT |= (1<<LCD_D5);
  else LCD_D5_PORT &= ~(1<<LCD_D5);
       
  if (input_nibble & (1<<2)) LCD_D6_PORT |= (1<<LCD_D6);
  else LCD_D6_PORT &= ~(1<<LCD_D6);
       
  if (input_nibble & (1<<3)) LCD_D7_PORT |= (1<<LCD_D7);
  else LCD_D7_PORT &= ~(1<<LCD_D7);
}

void lcd_byte(unsigned char input_byte) {
  LCD_EN_PORT |= (1<<LCD_EN);
  lcd_nibble(input_byte>>4);
  LCD_EN_PORT &= ~(1<<LCD_EN);
  
  LCD_EN_PORT |= (1<<LCD_EN);
  lcd_nibble(input_byte);
  LCD_EN_PORT &= ~(1<<LCD_EN);
  
  _delay_us(100);
}

void lcd_cmd(unsigned char cmd) {
  LCD_RS_PORT &= ~(1<<LCD_RS);
  lcd_byte(cmd);
}

void lcd_data(unsigned char data) {
  LCD_RS_PORT |= (1<<LCD_RS);
  lcd_byte(data);
}

void lcd_init(void) {
  LCD_D4_DDR |= (1<<LCD_D4);
  LCD_D5_DDR |= (1<<LCD_D5);
  LCD_D6_DDR |= (1<<LCD_D6);
  LCD_D7_DDR |= (1<<LCD_D7);
  LCD_RS_DDR |= (1<<LCD_RS);
  LCD_EN_DDR |= (1<<LCD_EN);
  _delay_ms(15);
  LCD_RS_PORT &= ~(1<<LCD_RS);
  LCD_EN_PORT &= ~(1<<LCD_EN);
  
  LCD_EN_PORT |= (1<<LCD_EN);
  lcd_nibble(0x03);
  LCD_EN_PORT &= ~(1<<LCD_EN);
  _delay_us(100);
  LCD_EN_PORT |= (1<<LCD_EN);
  lcd_nibble(0x03);
  LCD_EN_PORT &= ~(1<<LCD_EN);
  _delay_us(100);
  LCD_EN_PORT |= (1<<LCD_EN);
  lcd_nibble(0x03);
  LCD_EN_PORT &= ~(1<<LCD_EN);
  _delay_us(100);
  LCD_EN_PORT |= (1<<LCD_EN);
  lcd_nibble(0x02);
  LCD_EN_PORT &= ~(1<<LCD_EN);
  _delay_us(100);
  
  lcd_cmd( HD44780_FUNCTION_SET | HD44780_4_BIT | HD44780_TWO_LINE | HD44780_FONT5x7 );
  lcd_cmd( HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF );
  lcd_cmd( HD44780_ENTRY_MODE );  
  lcd_cmd( HD44780_CLEAR );
  _delay_ms(2);
}

void lcd_clear(void) {
  lcd_cmd( HD44780_CLEAR );
  _delay_ms(2);
}

void lcd_set_cursor(unsigned char x, unsigned char y) {
  unsigned char xy = x + y * 0x40;
  lcd_cmd((xy | 0x80));
}

void lcd_move_cursor_left(void) {
  lcd_cmd( HD44780_DISPLAY_CURSOR_SHIFT | HD44780_SHIFT_CURSOR | HD44780_SHIFT_LEFT );
}

void lcd_move_cursor_right(void) {
  lcd_cmd( HD44780_DISPLAY_CURSOR_SHIFT | HD44780_SHIFT_CURSOR | HD44780_SHIFT_RIGHT );
}

void lcd_print_char(char data) {
  lcd_data(data);
}

void lcd_print_str(char *data) {
  while (*data) lcd_data(*data++);
}