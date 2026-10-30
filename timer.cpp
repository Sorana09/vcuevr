#include <stdint.h>
#include "timer.h"

volatile uint32_t timer = TIMER_START;
void timer_reset(void){
  timer = TIMER_START;
}

uint8_t timer_done(void){
  timer--;
  if(timer == 0){
    timer_reset();
    return 1;
  }
  return 0;
}