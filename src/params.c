#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "params.h"

void put(char key[20], char value[20], struct Params* params){
	snprintf(params->keys[params->size], 20, "%s", key);
	snprintf(params->values[params->size], 20, "%s", value);
	params->size++;
}

void initParams(int argc, char* argv[], struct Params* params) {
	params->size= 0;
	strncpy(params->text, argv[1], sizeof(params->text) - 1);
	int i;
	for (i = 2; i < argc; i+=2) {
		if (argv[i][0] == '-' && argv[i+1][0] != '-') {
			put(argv[i], argv[i+1], params);
		} else {
			exit(EXIT_FAILURE);
		}
	}
}

int has(char* key, struct Params* params) {
	int i;
	for (i = 0; i < params->size; i++) {
		if (strcmp(key, params->keys[i]) == 0) {
			return i;
		}
	}
	return -1;
}

void freeParams(struct Params* params) {
	free(params->text);
}
