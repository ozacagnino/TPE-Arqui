#include <usr_stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys_calls.h>
#include <colores.h>
#include "eliminator.h"
#include "shell.h"

#define MAX_BUFFER 254
#define MAX_COMMANDS 10

char line[MAX_BUFFER+1] = {0}; //asi me aseguro que al menos va haber un cero
char parameter[MAX_BUFFER+1] = {0};
char command[MAX_BUFFER+1] = {0};
int linePos = 0;
char lastc;
const char * commands[] = {"undefined","help","time","clear","eliminator","inforeg","zerodiv","invopcode","sizeplus","sizeminus"};

void showCommands(){
	printString("\n-eliminator-         inicia el juego de eliminator",MAX_BUFFER);
	printString("\n-time-               muestra la hora actual en pantalla",MAX_BUFFER);
	printString("\n-clear-              limpia la pantalla",MAX_BUFFER);
	printString("\n-inforeg-            imprime los valores de los registros",MAX_BUFFER);
	printString("\n-sizeplus-           aumenta el tamanio de letra",MAX_BUFFER);
	printString("\n-sizeminus-          disminuye el tamanio de letra",MAX_BUFFER);
	printString("\n-zerodiv-            testeo de excepcion de division por cero",MAX_BUFFER);
	printString("\n-invopcode-          testeo codigo de operacion invalido",MAX_BUFFER);
	printChar('\n');
}

// static Color BLACK = {0,0,0};
// static Color WHITE = {255,255,255};
// static Color RED = {0,0,255};
// static Color LIGHT_BLUE = {255,255,255};
// static Color BLUE = {255,0,0};
// static Color ORANGE = {16,160,255};
// static Color YELLOW = {30,224,255};
// static Color PURPLE = {255,32,160};
// static Color PINK = {100,0,244};

static void newLine();
static void printLine(char c);
static int checkLine();
static void undefinedCommand();
static void helpCommand();
static void timeCommand(); 
static void clearCommand();
static void eliminatorCommand();
static void infoRegCommand();
static void zeroDivisionCommand();
static void invalidOpCodeCommand();
static void upscaleCommand();
static void downscaleCommand();


static void (*commands_ptr[MAX_COMMANDS])() = {undefinedCommand, helpCommand, timeCommand, clearCommand, eliminatorCommand, infoRegCommand, zeroDivisionCommand,invalidOpCodeCommand,
											   upscaleCommand,downscaleCommand};


void shell (){
	char c;
	printString("$ User> ",9);

	while(1){
		c = getChar();
		printLine(c);
	};
}

static void printLine(char c){
	if (linePos < MAX_BUFFER && c != lastc){
		if (isChar(c) || c == ' ' ||isDigit(c)){
			line[linePos++] = c;
			printChar(c);
		} else if (c == '\b' && linePos > 0){
			printChar(c);
			line[--linePos] = 0;
		} else if (c == '\n'){
			newLine();
		}
	}
	lastc = c;
}


static void newLine(){
	int i = checkLine();

	(*commands_ptr[i])();

	for (int i = 0; line[i] != '\0' ; i++){
		line[i] = 0;
		command[i] = 0;
		parameter[i] = 0;
	}
	linePos = 0;

	if (i != 3 ){
		printString("\n$ User> ",9);
	} else {
		printString("$ User> ",9);
	}
}

//separa comando de parametro
static int checkLine(){
	int i = 0;
	int j = 0;
	int k = 0;
	for ( j = 0 ; j < linePos && line[j] != ' ' ; j ++){
		command[j] = line[j];
	}
	if (j < linePos){
		j++;
		while (j < linePos){
			parameter[k++] = line[j++];
		}
	}

	for (i = 1 ; i < MAX_COMMANDS ; i++ ){
		if (strcmp(command,commands[i]) == 0){
			return i;
		}
	}

	return 0;
}


static void helpCommand(){
	printString("\n---HELP---\n",MAX_BUFFER);
	showCommands();
}

static void undefinedCommand(){
	printString("\n\nNo se reconoce \"",MAX_BUFFER);
	printString(command,MAX_BUFFER);
	printString("\" como un comando valido, para ver los comandos disponibles escribir \"help\"\n",MAX_BUFFER);
}

static void timeCommand(){
	display_time();
}


static void eliminatorCommand(){
	if(!startEliminator(charToInt(parameter))){
		printString("\nParametro invalido. Utilice 'eliminator 1' o 'eliminator 2' para comenzar el juego\n",MAX_BUFFER);
	}
	
}

static void clearCommand(){
	clear_scr();
}

static void infoRegCommand(){
	inforeg();
}

static void invalidOpCodeCommand(){
	test_invopcode();
}

static void zeroDivisionCommand(){
	test_zerodiv();
}

static void upscaleCommand(){
	increaseScale();
}

static void downscaleCommand(){
	decreaseScale();
}

