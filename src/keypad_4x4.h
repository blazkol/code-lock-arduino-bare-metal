// Port configuration

#define KEYPAD_R1_PORT  PORTD
#define KEYPAD_R1_DDR   DDRD
#define KEYPAD_R1       4

#define KEYPAD_R2_PORT  PORTD
#define KEYPAD_R2_DDR   DDRD
#define KEYPAD_R2       5

#define KEYPAD_R3_PORT  PORTD
#define KEYPAD_R3_DDR   DDRD
#define KEYPAD_R3       6

#define KEYPAD_R4_PORT  PORTD
#define KEYPAD_R4_DDR   DDRD
#define KEYPAD_R4       7

#define KEYPAD_C1_PORT  PORTB
#define KEYPAD_C1_PIN   PINB
#define KEYPAD_C1_DDR   DDRB
#define KEYPAD_C1       0

#define KEYPAD_C2_PORT  PORTB
#define KEYPAD_C2_PIN   PINB
#define KEYPAD_C2_DDR   DDRB
#define KEYPAD_C2       1

#define KEYPAD_C3_PORT  PORTB
#define KEYPAD_C3_PIN   PINB
#define KEYPAD_C3_DDR   DDRB
#define KEYPAD_C3       2

#define KEYPAD_C4_PORT  PORTB
#define KEYPAD_C4_PIN   PINB
#define KEYPAD_C4_DDR   DDRB
#define KEYPAD_C4       3

// Function declarations

void keypad_init(void);
char keypad_read(void);
char keypad_get_key(void);