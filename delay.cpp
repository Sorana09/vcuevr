#include <stdint.h>
#include "delay.h"

static volatile uint32_t timer = DELAY_START;
void delay_reset(void){
  timer = DELAY_START;
}

uint8_t delay_done(void){
  timer--;
  if(timer == 0){
    delay_reset();
    return 1;
  }
  return 0;
}