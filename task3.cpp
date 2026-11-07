#include <Arduino.h>
#include "tasks.h"

ISR(INT0_vect){
  PORTD ^= (1<<PD3);
}

void task3 (){
  DDRD |= (1<<PD3);
  DDRD &= ~(1<<PD2);
  PORTD |= (1<<PD2);

  EICRA |= (1<<ISC01);
  EIMSK |= (1<<INT0);

}