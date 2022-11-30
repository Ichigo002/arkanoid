#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <string>
#include <iostream>

#include "../ErrorHandler/ErrorHandler.h"
#include "../TextAsset/TextAsset.h"
#include "../SceneManager/SceneManager.h";
#include "../Scenes/AllScenes.h"

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
	TextAsset* txt;

	SceneManager* sman;

	SDL_Joystick* joystick;

	bool running;
};

#endif