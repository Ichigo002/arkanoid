#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <string>
#include <iostream>

#include "../ErrorHandler/ErrorHandler.h"
#include "../TextAsset/TextAsset.h"
#include "../SceneManager/SceneManager.h"
//#include "../SceneManager/SceneChanger.h"
#include "../Scenes/AllScenes.h"
#include "../KeyJoy/KeyJoy.h"
#include "Running.h"

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

	SceneManager* sman;
};

#endif