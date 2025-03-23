#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "config.h"
#include "params.h"

#define WINDOW_TITLE "Toast"
#define FONT "/usr/share/fonts/truetype/freefont/FreeSans.ttf"

struct Theme* theme = NULL;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;
struct Params* params = NULL;
struct ToastConfig* config = NULL;
bool running;


bool init(int argc, char* argv[]) {
	//Init SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow(WINDOW_TITLE, 100, 100, 200, 100, SDL_WINDOW_BORDERLESS);
	renderer = SDL_CreateRenderer(window, -1, 0);
	TTF_Init();
	theme = mainTheme();
	font = TTF_OpenFont(FONT, 24);
	initParams(argc, argv, params);
	initToastConfig(params,config); 
	return true;
}

void input() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				running = false;
				break;
			default:
				break;
		}
	}
}

void update() {
	SDL_Delay(16);
}

void render() {
	setColor(renderer, theme->background); 
	SDL_RenderClear(renderer);

	setColor(renderer, theme->textContainer);	
	SDL_Rect textContainer = {
		25,
		25,
		150,
		50
	};
	SDL_RenderFillRect(renderer, &textContainer);
	
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, "du texte a la la", *theme->text);
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect textRect = {25, 25, textSurface->w, textSurface->h};
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);


	SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]){
	running = init(argc, argv);
	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);
	printf("%d, %d", dm.w, dm.h);
	//Content
	while (running) {
		input();
		update();
		render();
	}

	//Free memory and quit
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	freeTheme(theme);
	freeParams(params);
	freeToastConfig(config);
	return EXIT_SUCCESS;
}

