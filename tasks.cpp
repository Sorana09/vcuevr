#include <Arduino.h>
#include "tasks.h"
#include "timer.h"

static int pas = 0;
static uint8_t button = 0, oldButton = 0;

void pins_init(void) {
  DDRC |= (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC4) | (1<<PC5);
  DDRD &= ~(1<<PD4);
  PORTD |= (1<<PD4);
}

void task1(void) {
  if (timer_done()) {
    pas++;
    if (pas > 3) {
      PORTC &= ~0b110;
      pas = 0;
    } else {
      PORTC |= (1 << (pas - 1));
    }
  }
}

void task2(void) {
  button = !(PIND & (1<<PD4));
  if (button == 1 && oldButton == 0) {
    PORTC ^= (1<<PC4) | (1<<PC5);
  }
  oldButton = button;
}