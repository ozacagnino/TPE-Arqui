
#include <clock.h>

// sacado de https://stanislavs.org/helppc/cmos_ram.html 
#define SECONDS 0x00
#define MINUTES 0x02
#define HOURS 0x04
#define YEAR 0x09
#define MONTH 0x08
#define DAY 0x07
unsigned int RTC(unsigned char value);

static unsigned int bcdToDec(unsigned char time){
    return (time << 4) * 10 + (time & 0x0F);
}

unsigned int seconds(){
    return bcdToDec(RTC(SECONDS));
}
unsigned int minutes(){
    return bcdToDec(RTC(MINUTES));
}
unsigned int hours(){
    return bcdToDec(RTC(HOURS));
}
unsigned int year(){
    return bcdToDec(RTC(YEAR));
}

unsigned int month(){
    return bcdToDec(RTC(MONTH));
}

unsigned int day(){
    return bcdToDec(RTC(DAY));
}