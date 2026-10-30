#include <Arduino.h>
#include "tasks.h"
#include "delay.h"
static int pas = 0;
static uint8_t button = 0, oldButton = 0;
static uint8_t state = 0; // 0-pc5, 1-pc4

void pins_init(void) {
  DDRC |= (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC4) | (1<<PC5);
  DDRD &= ~(1<<PD4); 
  PORTD |= (1<<PD4);
}

void task1(void) {
  if (delay_done()) {
    pas++;
    if (pas > 3) {
      PORTC &= ~0b110;
      pas = 0;
    } else {
      PORTC |= (1 << (pas - 1));
    }
  }
}

void task2(void){
  button = !(PIND & (1<<PD4));
  if (button == 1 && oldButton == 0) {
    state = (state + 1) % 2;
    //PORTC &= ~((1<<PC4) | (1<<PC5)); //both off
    if(state == 1) {
      PORTC = (1<<PC4);
    }
    else if(state == 0){
      PORTC = (1<<PC5);
    }
  }
  oldButton = button;
}

ISR(INT0_vect){
  PORTC ^= (1<<PC3);
}

void task3(){
  DDRC |= (1<<PC3);
  PORTD |= (1<<PD2);
  EICRA |= (1<<ISC01);  // set the event
  EIMSK |= (1<<INT0); 
  sei();
}

