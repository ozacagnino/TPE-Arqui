#include <stdint.h>
#include "videoDriver.h"
#include "time.h"


#define ZERO_ID 0
#define INVAL_OPCODE_ID 6

extern void reset();
extern int _hlt(void);

Color red = {30,30,255};
Color white = {255,255,255};
Color black = {0,0,0};
Color blue = {255,0,0};


const char * registers[18] = {
    "RAX", "RBX", "RCX", "RDX", "RSI", "RDI", "RBP", "RSP", "R8 ", "R9 ", "R10", "R11", "R12", "R13", "R14", "R15", "RIP", "RFLAGS "
};

static void uint64ToHex(uint64_t n, char buf[16]) {
    int i=15;
    do { 
        int digit = n % 16; // digit = n mod 16
        buf[i] = (digit < 10 ? '0' : ('A' - 10)) + digit; // buf[i] = digit + '0' o 'A' - 10
        n /= 16;
    } while(i-- != 0); 
}


void exception_handler(int exception, const uint64_t register_data[17]) { // 17 porque el ultimo es el rflags
	videoDriver_prints("\nERROR: ",red,black); 
	char buf[19];
    buf[0] = '0';
    buf[1] = 'x';
    buf[18] = '\0';

	if (exception == ZERO_ID){ // zero division
		videoDriver_prints("zero division detected\n",white, black);
	} else if (exception == INVAL_OPCODE_ID){ // invalid opcode
		videoDriver_prints("invalid op code detected\n", white, black);
	}

	for (int i = 0; i < 16; i++) { // 16 registros
        videoDriver_prints(registers[i],white,black); // nombre del registro
        videoDriver_prints(": ",white,black); // separador
        uint64ToHex(register_data[i], buf+2); // valor del registro
        videoDriver_prints(buf,white,black); // lo imprimo
        if (i % 4 == 3)
            videoDriver_newline(); // cada 4 registros cambio de linea
        else 
            videoDriver_prints("   ",white,black);
    }

    reset();
}
