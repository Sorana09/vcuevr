#include <Arduino.h>
#include "tasks.h"

static uint8_t duty = 0;
static int8_t dir = 1;
static uint8_t ms5 = 0;

ISR(TIMER0_COMPA_vect){
  ms5 ++;
  if(ms5 >= 4){ //evry 4 ms
    ms5 = 0;
    if(duty == OCR0A){
      dir = -1;
    }
    else if(duty == 0){
      dir = 1;
    }
    duty += dir;
    OCR0B = duty; // give the new brightness to the timer
  }
}

 void task5(){
  DDRD |= (1<<PD5);

  TCCR0A = (1<<COM0B1) | (1<<WGM01) | (1<<WGM00);//connects the timer to pin 5 and picks pwm mode
  TCCR0B = (1<<WGM02) | (1<<CS01) | (1<<CS00); //fast pwm, top = ocr0a + prescaler /64

  TCNT0 = 0;
  OCR0A = 249;
  OCR0B = 0;//brightness starts from 0%

  TIMSK0 |= (1<<OCIE0A);
}