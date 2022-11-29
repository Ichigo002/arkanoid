#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <string>

#include "../ErrorHandler/ErrorHandler.h"
#include "../TextAsset/TextAsset.h"

class Game
{
public:
	Game();
	~Game();

	void run();
	void update();
	void draw();
	void events();

private:
	int _init_SDL();
	int _init_objects();
private:
	SDL_Window* win;
	SDL_Renderer* ren;
	SDL_Event* eve;

	FontAsset* font;

	bool running;
};

#endif