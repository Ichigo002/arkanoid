#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>

class Scene
{
public:
	Scene(SDL_Renderer* r, SDL_Event* e)
		: ren(r), eve(e) { ; }
	virtual ~Scene() = 0;

	virtual void update() = 0;
	virtual void events() = 0;
	virtual void draw() = 0;

	virtual void OnLoad() = 0;
	virtual void OnUnload() = 0;

protected:
	SDL_Event* eve;
	SDL_Renderer* ren;
};

#endif