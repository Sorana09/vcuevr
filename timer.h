#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#define TIMER_START 200000

void timer_reset(void);
uint8_t timer_done(void);

#endif