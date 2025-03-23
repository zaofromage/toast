#include <stdio.h>
#include <string.h>
#include "params.h"

#ifndef CONFIG_H
#define CONFIG_H

struct Theme {
	SDL_Color *background;
	SDL_Color *textContainer;
	SDL_Color *text;
};

struct Position {
	int x;
	int y;
};

struct Position *getPosition(char *place, int w, int h, int screenW, int screenH);

struct ToastConfig {
	struct Position *position;
	char *text;
	int w;
	int h;
};

struct Theme* mainTheme();
void freeTheme(struct Theme* theme);
void setColor(SDL_Renderer* renderer, SDL_Color* color);
void initToastConfig(struct Params* params, struct ToastConfig* config);
void freeToastConfig(struct ToastConfig* config);


#endif //CONFIG_H
