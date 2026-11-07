#include <Arduino.h>
#include "tasks.h"
#include "pinsInit.h"

static uint8_t button = 0, oldButton = 0;
static uint8_t state = 0;
void pinsinitTask2(){
  DDRC |= (1<<PC4) | (1<<PC5);
  DDRD &= ~(1<<PD4); // button as input
  PORTD |= (1<<PD4);
}

void task2(){
  button = !(PIND & (1<<PD4));
  if(button == 1 && oldButton == 0){
    state = (state + 1) % 2;
    PORTC &= ~((1<<PC4) | (1<<PC5));
    if(state == 1){
      PORTC |= (1<<PC4);
    }
    else if(state == 0){
      PORTC |= (1<<PC5);
    }
  }
  oldButton = button;
}