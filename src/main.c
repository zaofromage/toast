#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#include "config.h"

#define WINDOW_TITLE "Toast"
#define FONT "/usr/share/fonts/truetype/freefont/FreeSans.ttf"

struct Theme* theme = NULL;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;
struct Params* params = NULL;
struct ToastConfig* config = NULL;
bool running;

void* delayEnd(void* vargp) {
	int duration = *(int*)vargp;
	int i = 0;
	while (i++ < duration && running) {
		sleep(1);
	}
	running = false;
	return NULL;
}

bool init(int argc, char* argv[]) {
	//Init SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	TTF_Init();
	theme = mainTheme();
	font = TTF_OpenFont(FONT, 24);
	config = initToastConfig(argc, argv); 
	window = SDL_CreateWindow(WINDOW_TITLE, config->position->x, config->position->y, config->w, config->h, SDL_WINDOW_BORDERLESS);
	renderer = SDL_CreateRenderer(window, -1, 0);
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
	// backgournd
	setColor(renderer, theme->background); 
	SDL_RenderClear(renderer);

	// text container
	setColor(renderer, theme->textContainer);	
	SDL_Rect textContainer = {
		10,
		10,
		config->w - 20,
		config->h - 20
	};
	SDL_RenderFillRect(renderer, &textContainer);
	
	// text
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, config->text, *theme->text);
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect textRect = {25, 25, textSurface->w, textSurface->h};
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);


	SDL_RenderPresent(renderer);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

int main(int argc, char* argv[]){
	running = init(argc, argv);
	pthread_t t_id;
	pthread_create(&t_id, NULL, delayEnd, &(config->duration));
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
	pthread_join(t_id, NULL);
	freeTheme(theme);
	freeToastConfig(config);
	return EXIT_SUCCESS;
}

