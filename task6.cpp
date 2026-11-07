#include <Arduino.h>
#include "tasks.h"

ISR(ADC_vect){
  OCR2A = ADCH;
}

void task6(){
  DDRB |= (1<<PB3);
  DDRC &= ~(1<<PC0);
  
  TCCR2A = (1<<COM2A1) | (1<<WGM21) | (1<<WGM20); //oc2a - set output pin and fasst pwm
  TCCR2B = (1<<CS22); //prescaler 64

  OCR2A = 0; //duty cycle to 0
  ADMUX = (1<<REFS0) | (1<<ADLAR); // uses 5v
  ADCSRB = 0;
  ADCSRA = (1<<ADEN) | (1<<ADATE) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) | (1<<ADIF);
  // enables ADC hardware / auto-triggering / ADC conversion complete interrupt and prescaler 128 for optimal clock

  ADCSRA |= (1<<ADSC);
}