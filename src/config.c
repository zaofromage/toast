#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <ctype.h>
#include "config.h"

struct Theme* mainTheme() {
	struct Theme* theme = malloc(sizeof (struct Theme));
	if (theme == NULL) return NULL;
	theme->background = malloc(sizeof (SDL_Color));
	theme->background->r = 57;
	theme->background->g = 169;
	theme->background->b = 41;
	theme->background->a = 255;

	theme->textContainer = malloc(sizeof (SDL_Color));
	theme->textContainer->r = 63;
	theme->textContainer->g = 221;
	theme->textContainer->b = 40;
	theme->textContainer->a = 255;

	theme->text = malloc(sizeof (SDL_Color));
	theme->text->r = 0;
	theme->text->g = 0;
	theme->text->b = 0;
	theme->text->a = 255;
	return theme;
}

void freeTheme(struct Theme* theme) {
	free(theme->background);
	free(theme->textContainer);
	free(theme->text);
	free(theme);
}

void setColor(SDL_Renderer *renderer, SDL_Color* color) {
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
}

struct Position* getPosition(char *place, int w, int h, int screenW, int screenH) {
	for ( ; *place; ++place) *place = tolower(*place);
	struct Position *res = malloc(sizeof(struct Position));
	if (strcmp(place, "topleft") == 0) {
		res->x = 50;
		res->y = 50;
	} else if (strcmp(place, "topright") == 0) {
		res->x = screenW - w - 50;
		res->y = 50;
	} else if (strcmp(place, "bottomleft") == 0) {
		res->x = 50;
		res->y = screenH - h - 50;
	} else if (strcmp(place, "bottomright") == 0) {
		res->x = screenW - w - 50;
		res->y = screenH - h - 50;
	} else {
		res->x = screenW - w - 50;
		res->y = screenH - h - 50;
	}
	return res;
}
	
/**
 * -t text
 * -p position {topleft, topright, bottomleft, bottomright}
 * -d delay before end
 * -w width
 * -h height
 */
struct ToastConfig* initToastConfig(int argc, char** argv) {
	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);
	struct ToastConfig* config = malloc(sizeof(struct ToastConfig));
	if (!config) return NULL;
	if (hasParam("-t", argc, argv)) {
		char* text = getParam("-t", argc, argv);
		config->text = strdup(text);
		free(text);
	} else {
		config->text = strdup("Texte par defaut");
	}
	if (hasParam("-w", argc, argv)) {
		config->w = atoi(getParam("-w", argc, argv));
	} else {
		config->w = 200;
	}
	if (hasParam("-h", argc, argv)) {
		config->h = atoi(getParam("-h", argc, argv));
	} else {
		config->h = 75;
	}
	if (hasParam("-p", argc, argv)) {
		char* place = getParam("-p", argc, argv);
		config->position = getPosition(place, config->w, config->h, dm.w, dm.h);
		free(place);
	} else {
		config->position = getPosition("bottomright", config->w, config->h, dm.w, dm.h);
	}

	if (hasParam("-d", argc, argv)){
		config->duration = atoi(getParam("-d", argc, argv));
	} else {
		config->duration = 5;
	}
	return config;
}

void freeToastConfig(struct ToastConfig* config) {
	free(config->position);
	free(config->text);
}

bool hasParam(const char* head, int argc, char** argv) {
	int i;
	for (i = 0; i < argc-1; i++) {
		if (strcmp(head, argv[i]) == 0) {
			return true;
		}
	}
	return false;
}

char* getParam(const char* head, int argc, char** argv) {
    for (int i = 0; i < argc; i++) {
        if (strcmp(head, argv[i]) == 0) {
            if (i + 1 < argc && argv[i + 1][0] != '-') {
		printf("%d", i+1);
                return strdup(argv[i + 1]);
            } else {
                fprintf(stderr, "Error : %s must be followed by a valid value (toast --help)\n", head);
                exit(EXIT_FAILURE);
            }
        }
    }
    return NULL;
}
