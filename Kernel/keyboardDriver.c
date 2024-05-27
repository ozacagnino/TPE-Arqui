#include <keyboardDriver.h>
#include <naiveConsole.h>

extern unsigned int get_key();

#define PRESS 1
#define RELEASE 2
#define ERROR -1

//#define BUFF_LEN 30
//static int buffSize=0; //cantidad de elementos del buffer
static int ridx=0; //posicion de escritura
static int widx=0; //posicion de lectura

#define LEFT_SHIFT 0x2A
#define RIGHT_SHIFT 0x36
#define CAPS_LOCK 0x3A
#define CTRL 0x1D

#define BUFFER_LENGHT 256

static char keyMapRow = 0;
static uint8_t buffer[BUFFER_LENGHT];
//extern unsigned int keyRead();

uint16_t start = 0;
uint16_t end = 0;

//static char buffer[BUFF_LEN]={0};

static int shift = 0;
static int ctrl = 0;
static int capsLock = 0;

static uint8_t scancodeLToAscii[] = {

      0,   27, '1', '2', '3', '4', '5', '6', '7', '8', '9',  '0', '-', '=',
   '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',  '[', ']',
   '\n',    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
      0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',    0, '*',
      0,  ' ',   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,
      0,    0,   0,   0, '-',   0,   0,   0, '+',   0,   0,   0,    0,   0,
      0,    0,   0,   0,   0,   0

};

static uint8_t scancodeUToAscii[] = {

      0,   27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+',
   '\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}',
   '\n',    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
      0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',   0, '*',
      0, ' ',    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,    0,   0, '-',   0,   0,   0, '+',   0,   0,   0,   0,   0,
      0,   0,    0,   0,   0,   0

};

static uint8_t * keyMap[] = {scancodeLToAscii, scancodeUToAscii};

/* char getCharCode(int key){
    return ScanCodes[key];
} */

unsigned int getScanCode(){
  return get_key();
}

unsigned char ctoi(unsigned char mChar){
    return keyMap[0][mChar];
}

void addBuffer(uint8_t c){

  buffer[end++] = c;

  if(end == BUFFER_LENGHT)
    end = 0;
  return;
}

void keyboard_handler()
{

	unsigned char code = get_key();
	if(code < 0x80){    // Key pressed
        if(code == LEFT_SHIFT || code == RIGHT_SHIFT){
        keyMapRow |= 0x01;
        }
        else if(keyMap[keyMapRow][code]!=0){
        addBuffer(keyMap[keyMapRow][code]);
        }
	} else {               // Key released
        code-=0x80;
        if(code == LEFT_SHIFT || code == RIGHT_SHIFT){  
        keyMapRow &= 0xFE;
        }
	}

  return;
}

char * tryKeyboard()
{
//   for(int i=0 ; i< 50 ; ++i){
    keyboard_handler();
//   }
  buffer[end] = 0;
  return buffer;
}