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
	if (strcmp(place, "topleft")) {
		res->x = 50;
		res->y = 50;
	} else if (strcmp(place, "topright")) {
		res->x = screenW - w - 50;
		res->y = 50;
	} else if (strcmp(place, "bottomleft")) {
		res->x = 50;
		res->y = screenH - h - 50;
	} else if (strcmp(place, "bottomright")) {
		res->x = screenW - w - 50;
		res->y = screenH - h - 50;
	} else {
		res->x = screenW - w - 50;
		res->y = screenH - h - 50;
	}
	return res;
}
	
void initToastConfig(struct Params* params, struct ToastConfig* config) {
	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);
	config->text = strdup(params->text);
	config->w = 200;
	config->h = 75;
	int placeInd = has("-p", params);
	if (placeInd > 0) {
		config->position = getPosition(params->values[placeInd], 200, 75, dm.w, dm.h);
	}
}

void freeToastConfig(struct ToastConfig* config) {
	free(config->position);
	free(config->text);
}
