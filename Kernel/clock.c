
#include <clock.h>

// sacado de https://stanislavs.org/helppc/cmos_ram.html 
#define SECONDS 0x00
#define MINUTES 0x02
#define HOURS 0x04
#define YEAR 0x09
#define MONTH 0x08
#define DAY 0x07

unsigned int get_seconds();
unsigned int get_hours();
unsigned int get_minutes();

static unsigned int bcdToDec(unsigned char time){
    return (time << 4) * 10 + (time & 0x0F);
}

unsigned int seconds(){
    return get_seconds();
}
unsigned int minutes(){
    return get_minutes();
}
unsigned int hours(){
    return get_hours();
}
// unsigned int year(){
//     return get;
// }

// unsigned int month(){
//     return (RTC(MONTH));
// }

// unsigned int day(){
//     return (RTC(DAY));
// }