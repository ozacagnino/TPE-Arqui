/* En Kernel/include/clock.h */

#ifndef CLOCK_H
#define CLOCK_H

/* Returns RTC seconds */
unsigned int seconds();

/* Returns RTC minutes */
unsigned int minutes();

/* Returns RTC hour */
unsigned int hours();

/* Returns RTC year */
unsigned int year();

/* Returns RTC month */
unsigned int month();

/* Returns RTC day */
unsigned int day();


#endif