#include <Arduino.h>
#include "tasks.h"
#include "pinsInit.h"
#include "delay.h"

#define LED_MASK ((1<<PC1) | (1<<PC2) | (1<<PC3))
static int pas = 0;
static volatile uint8_t led4 = 0;

void pinsinitTask1_4(){
  DDRC |= LED_MASK;
}

void task1(){
  if (delay_done()) {
    pas++;
    if (pas > 3) {
      PORTC &= ~LED_MASK;
      pas = 0;
    } else {
      PORTC |= (1 << pas);
    }
  }
}

ISR(TIMER1_COMPA_vect){
  led4 = (led4 + 1) % 4;
  PORTC = (PORTC & ~LED_MASK) | (((1<<led4) - 1) << PC1); 
}

void task4(){
  DDRC |= LED_MASK;
  led4 = 1;

  PORTC = (PORTC & ~LED_MASK);
  TCCR1A = 0;
  TCCR1B = (1<<WGM12) | (1<<CS12); //ctc mode + prescaler  256
  TCNT1 = 0;
  OCR1A = 15624;
  TIMSK1 = (1<<OCIE1A);

}