/* sampleCodeModule.c */
#include <sys_calls.h>
#include <stdint.h>
#include <usr_stdlib.h>
#include <shell.h>

char * v = (char*)0xB8000 + 79 * 2;

int main() {
	
	showCommands();

	shell();

	return 0;
} 