#ifndef _TIME_H_
#define _TIME_H_

#include <stdint.h>
#include <math.h>


uint64_t getHours();

uint64_t getMinutes();

uint64_t getSeconds();

void display_time();

void sleep(int millis);

#endif
