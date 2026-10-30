#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>
#define DELAY_START 200000

void delay_reset(void);
uint8_t delay_done(void);

#endif