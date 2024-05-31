#include <sys_calls.h>
#include <usr_stdlib.h>

#define GMT -3

int getHours(){
	return sys_getHours();
}

int getMinutes(){
	return sys_getMinutes();
}

int getSeconds(){
	return sys_getSeconds();
}

void display_time(){
	int hours, minutes, seconds;

	hours = getHours() + GMT;
	minutes = getMinutes();
	seconds = getSeconds();
	
	printChar('\n');
	printHex(hours);
	printChar(':');
	printHex(minutes);
	printChar(':');
	printHex(seconds);
}


