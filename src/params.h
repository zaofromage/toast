#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#ifndef PARAMS_H
#define PARAMS_H

struct Params {
	char text[30];
	char keys[10][20];
	char values[10][20];
	int size;
};

void put(char key[20], char value[20], struct Params* params); 
void initParams(int argc, char* argv[], struct Params* params);
int has(char *key, struct Params* params);
void freeParams(struct Params* params);

#endif //PARAMS_H
