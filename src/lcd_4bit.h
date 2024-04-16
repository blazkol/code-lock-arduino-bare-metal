// Port configuration

#define LCD_RS_PORT     PORTD
#define LCD_RS_DDR      DDRD
#define LCD_RS          2

#define LCD_EN_PORT     PORTD
#define LCD_EN_DDR      DDRD
#define LCD_EN          3

#define LCD_D4_PORT     PORTC
#define LCD_D4_DDR      DDRC
#define LCD_D4          3

#define LCD_D5_PORT     PORTC
#define LCD_D5_DDR      DDRC
#define LCD_D5          2

#define LCD_D6_PORT     PORTC
#define LCD_D6_DDR      DDRC
#define LCD_D6          1

#define LCD_D7_PORT     PORTC
#define LCD_D7_DDR      DDRC
#define LCD_D7          0

// HD44780 instruction set

#define HD44780_CLEAR   0x01

#define HD44780_HOME    0x02

#define HD44780_ENTRY_MODE				0x04
	#define HD44780_EM_SHIFT_CURSOR		0
	#define HD44780_EM_SHIFT_DISPLAY	1
	#define HD44780_EM_DECREMENT		0
	#define HD44780_EM_INCREMENT		2

#define HD44780_DISPLAY_ONOFF			0x08
	#define HD44780_DISPLAY_OFF			0
	#define HD44780_DISPLAY_ON			4
	#define HD44780_CURSOR_OFF			0
	#define HD44780_CURSOR_ON			2
	#define HD44780_BLINK_OFF	    	0
	#define HD44780_BLINK_ON    		1

#define HD44780_DISPLAY_CURSOR_SHIFT	0x10
	#define HD44780_SHIFT_CURSOR		0
	#define HD44780_SHIFT_DISPLAY		8
	#define HD44780_SHIFT_LEFT			0
	#define HD44780_SHIFT_RIGHT			4

#define HD44780_FUNCTION_SET			0x20
	#define HD44780_FONT5x7				0
	#define HD44780_FONT5x10			4
	#define HD44780_ONE_LINE			0
	#define HD44780_TWO_LINE			8
	#define HD44780_4_BIT				0
	#define HD44780_8_BIT				16

#define HD44780_CGRAM_SET				0x40

#define HD44780_DDRAM_SET				0x80

// Function declarations

void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_init(void);
void lcd_clear(void);
void lcd_set_cursor(unsigned char y, unsigned char x);
void lcd_print(char * str);