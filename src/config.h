#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>

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
	int duration;
};

struct Theme* mainTheme();
void freeTheme(struct Theme* theme);
void setColor(SDL_Renderer* renderer, SDL_Color* color);
struct ToastConfig* initToastConfig(int argc, char** argv, TTF_Font* font);
void freeToastConfig(struct ToastConfig* config);
char* getParam(const char* head, int argc, char** argv);
bool hasParam(const char* head, int argc, char** argv);

#endif //CONFIG_H
