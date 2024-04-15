#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

char read_keypad();
char get_key();

long int timer2 = 0; //global variable incremented after each Timer2 interrupt

int main(void) {

  //setup

  DDRD = 0b11110000; //PORTD 4-7 connected to rows of keypad and declared as output
  PORTD = 0b00000000;
  DDRB = 0b00000000; //PORTB 0-3 connected to columns of keypad and declared as input with pull-ups
  PORTB = 0b00001111;   
  DDRC = 0b00110000; //PORTC 4-5 connected to LEDs and declared as output
  PORTC = 0b00000000;
  
  cli();
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  OCR2A = 0x9C;
  TCCR2A = 1 << WGM21;
  TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);
  TIMSK2 = (1 << OCIE2A);
  sei();

  char password[] = {'3', '5', '9', '3'};
  char input[] = {'-', '-', '-', '-'};
  char key;
  int i = 0;

  //main loop

  while(true) {
    if (i == 4) {
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
      i = 0;
    }

    key = get_key();
    if (key) {
      input[i] = key;
      i++;
    }
  }
}

char read_keypad() {
  PORTD = 0b11100000;
  if (!(PINB & (1<<PINB3))) { return 'A'; }
  else if (!(PINB & (1<<PINB0))) { return '1'; }
  else if (!(PINB & (1<<PINB1))) { return '2'; }
  else if (!(PINB & (1<<PINB2))) { return '3'; }

  PORTD = 0b11010000;
  if (!(PINB & (1<<PINB3))) { return 'B'; }
  else if (!(PINB & (1<<PINB0))) { return '4'; }
  else if (!(PINB & (1<<PINB1))) { return '5'; }
  else if (!(PINB & (1<<PINB2))) { return '6'; }

  PORTD = 0b10110000;
  if (!(PINB & (1<<PINB3))) { return 'C'; }
  else if (!(PINB & (1<<PINB0))) { return '7'; }
  else if (!(PINB & (1<<PINB1))) { return '8'; }
  else if (!(PINB & (1<<PINB2))) { return '9'; }

  PORTD = 0b01110000;
  if (!(PINB & (1<<PINB3))) { return 'D'; }
  else if (!(PINB & (1<<PINB0))) { return '*'; }
  else if (!(PINB & (1<<PINB1))) { return '0'; }
  else if (!(PINB & (1<<PINB2))) { return '#'; }

  return '\0';
}

char get_key() {
  static bool pressed = false; //variable that changes state after pressing / unpressing a key
  char key = read_keypad();

  if(key == '\0'){
    timer2 = 0;
    pressed = false;
  }
  else if (timer2 > 10 && pressed == false){
    pressed = true;
    return key;
  }
  return '\0';
}

ISR(TIMER2_COMPA_vect){
  timer2++;
}