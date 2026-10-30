#include "timer.h"

int i = 0, pas = 0;
uint8_t button = 0, oldButton = 0;

void setup() {
  DDRC |= (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC4) | (1<<PC5);
  //PORTC |= (1<<PC4);          
  //PORTC |= (1<<PC5);

  DDRD &= ~(1<<PD4);
  PORTD |= (1<<PD4);
}

void loop() {
  task1();
  task2();
}

void task2(){
  button = !(PIND & (1<<PC4));
  if (button == 1 && oldButton == 0) {
    PORTC ^= (1<<PC4) | (1<<PC5);       
  }
  oldButton = button;
}

void task1(){
  if (timer_done()) {
    pas++;

    if (pas > 3) {
      PORTC &= ~0b110; //turn off only a1/2  
      pas = 0;
    }
    else
    {
      PORTC |= (1 << (pas - 1));
    }
  }
}

