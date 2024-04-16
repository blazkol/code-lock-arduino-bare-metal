#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#include "keypad_4x4.h"

long int timer2 = 0; // global variable incremented after each Timer2 interrupt

void timer2_setup(void) {
  cli();
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  OCR2A = 0x9C;
  TCCR2A = 1 << WGM21;
  TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
  TIMSK2 = (1 << OCIE2A);
  sei();
}

void keypad_init(void) {
  timer2_setup();

  KEYPAD_R1_DDR |= (1<<KEYPAD_R1);
  KEYPAD_R2_DDR |= (1<<KEYPAD_R2);
  KEYPAD_R3_DDR |= (1<<KEYPAD_R3);
  KEYPAD_R4_DDR |= (1<<KEYPAD_R4);

  KEYPAD_C1_DDR &= ~(1<<KEYPAD_C1);
  KEYPAD_C2_DDR &= ~(1<<KEYPAD_C2);
  KEYPAD_C3_DDR &= ~(1<<KEYPAD_C3);
  KEYPAD_C4_DDR &= ~(1<<KEYPAD_C4);

  KEYPAD_C1_PORT |= (1<<KEYPAD_C1);
  KEYPAD_C2_PORT |= (1<<KEYPAD_C2);
  KEYPAD_C3_PORT |= (1<<KEYPAD_C3);
  KEYPAD_C4_PORT |= (1<<KEYPAD_C4);
}

char keypad_read(void) {
  KEYPAD_R1_PORT &= ~(1<<KEYPAD_R1);
  KEYPAD_R2_PORT |= (1<<KEYPAD_R2);
  KEYPAD_R3_PORT |= (1<<KEYPAD_R3);
  KEYPAD_R4_PORT |= (1<<KEYPAD_R4);
  if (!(KEYPAD_C4_PIN & (1<<KEYPAD_C4))) { return 'A'; }
  else if (!(KEYPAD_C1_PIN & (1<<KEYPAD_C1))) { return '1'; }
  else if (!(KEYPAD_C2_PIN & (1<<KEYPAD_C2))) { return '2'; }
  else if (!(KEYPAD_C3_PIN & (1<<KEYPAD_C3))) { return '3'; }

  KEYPAD_R1_PORT |= (1<<KEYPAD_R1);
  KEYPAD_R2_PORT &= ~(1<<KEYPAD_R2);
  KEYPAD_R3_PORT |= (1<<KEYPAD_R3);
  KEYPAD_R4_PORT |= (1<<KEYPAD_R4);
  if (!(KEYPAD_C4_PIN & (1<<KEYPAD_C4))) { return 'B'; }
  else if (!(KEYPAD_C1_PIN & (1<<KEYPAD_C1))) { return '4'; }
  else if (!(KEYPAD_C2_PIN & (1<<KEYPAD_C2))) { return '5'; }
  else if (!(KEYPAD_C3_PIN & (1<<KEYPAD_C3))) { return '6'; }

  KEYPAD_R1_PORT |= (1<<KEYPAD_R1);
  KEYPAD_R2_PORT |= (1<<KEYPAD_R2);
  KEYPAD_R3_PORT &= ~(1<<KEYPAD_R3);
  KEYPAD_R4_PORT |= (1<<KEYPAD_R4);
  if (!(KEYPAD_C4_PIN & (1<<KEYPAD_C4))) { return 'C'; }
  else if (!(KEYPAD_C1_PIN & (1<<KEYPAD_C1))) { return '7'; }
  else if (!(KEYPAD_C2_PIN & (1<<KEYPAD_C2))) { return '8'; }
  else if (!(KEYPAD_C3_PIN & (1<<KEYPAD_C3))) { return '9'; }

  KEYPAD_R1_PORT |= (1<<KEYPAD_R1);
  KEYPAD_R2_PORT |= (1<<KEYPAD_R2);
  KEYPAD_R3_PORT |= (1<<KEYPAD_R3);
  KEYPAD_R4_PORT &= ~(1<<KEYPAD_R4);
  if (!(KEYPAD_C4_PIN & (1<<KEYPAD_C4))) { return 'D'; }
  else if (!(KEYPAD_C1_PIN & (1<<KEYPAD_C1))) { return '*'; }
  else if (!(KEYPAD_C2_PIN & (1<<KEYPAD_C2))) { return '0'; }
  else if (!(KEYPAD_C3_PIN & (1<<KEYPAD_C3))) { return '#'; }

  return '\0';
}

char keypad_get_key(void) {
  static bool pressed = false;

  char key = keypad_read();

  if (key == '\0') {
    timer2 = 0;
    pressed = false;
  }
  else if (timer2 > 10 && pressed == false) {
    pressed = true;
    return key;
  }

  return '\0';
}

ISR(TIMER2_COMPA_vect){
  timer2++;
}