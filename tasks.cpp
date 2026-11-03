#include <Arduino.h>
#include "tasks.h"
#include "delay.h"
static int pas = 0;
static uint8_t button = 0, oldButton = 0;
static uint8_t state = 0; // 0-pc5, 1-pc4

static uint8_t led4 = 0; // 0-pc1 , 1-pc2, 2-pc3

static uint8_t duty = 0;   // 0 = 0%, 249 = 100%
static int8_t dir = 1;  
static uint8_t ms5 = 0;

void pins_init(void) {
  DDRC |= (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC4) | (1<<PC5);
  DDRD &= ~(1<<PD4); 
  PORTD |= (1<<PD4);
}

void task1(void) {
  if (delay_done()) {
    pas++;
    if (pas > 3) {
      PORTC &= ~0b111;
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
    PORTC &= ~((1<<PC4) | (1<<PC5)); //both off
    if(state == 1) {
      PORTC |= (1<<PC4);
    }
    else if(state == 0){
      PORTC |= (1<<PC5);
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
  EICRA |= (1<<ISC01);
  EIMSK |= (1<<INT0); 
}

ISR(TIMER1_COMPA_vect){
  //PORTC &= ~0b111;            
  led4 = (led4 + 1) % 4; 
  PORTC = (PORTC & ~0b111) | ((1<<led4) - 1);
}

void task4(){
  DDRC |= (1<<PC0) | (1<<PC1) | (1<<PC2); 
  led4 = 1;
  PORTC = (PORTC & ~0b111);

  TCCR1A = 0;
  TCCR1B = (1<<WGM12) | (1<<CS12);  // CTC mode, prescaler 256
  TCNT1  = 0;
  OCR1A  = 15624;                   // 0.25s
  TIMSK1 = (1<<OCIE1A);   
}

void task5(){
  DDRD |= (1<<PD5);

  TCCR0A = (1<<COM0B1) | (1<<WGM01) | (1<<WGM00); //Connects the timer to pin 5, and picks pwm mode
  TCCR0B = (1<<WGM02) | (1<<CS01) | (1<<CS00);    //mode 7 (fast PWM, TOP = OCR0A) + prescaler /64

  TCNT0 = 0;
  OCR0A = 249;
  OCR0B = 0;// brightness starts at 0%

  TIMSK0 |= (1<<OCIE0A);
}

ISR(TIMER0_COMPA_vect){
  ms5 ++;
  if(ms5 >= 4){ //evry 4 ms
    ms5 = 0;
    if(duty == 249){ // 100 % brighter then goes darker
      dir = -1;
    }
    else if(duty == 0){
      dir = 1;
    }
    duty += dir;
    OCR0B = duty; // give the new brightness to the timer
  }
}
