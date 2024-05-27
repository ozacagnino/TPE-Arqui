#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H
#include <naiveConsole.h>
#include <stdint.h>

//char getCharCode(int key);
unsigned int getScanCode();
unsigned char ctoi(unsigned char mChar);
char *  tryKeyboard();
void keyboard_handler();


#endif