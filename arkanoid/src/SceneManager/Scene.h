#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>
#include "../AudioPlayer/AudioPlayer.h"
#include "../KeyJoy/KeyJoy.h"
#include "SceneChanger.h"

class Scene
{
public:
	Scene(SDL_Renderer* r, AudioPlayer* ap, KeyJoy* k)
		: ren(r), audio(ap), kj(k) { ; }
	virtual ~Scene() { ; }

	virtual void update() = 0;
	virtual void events() { kj->events(); };
	virtual void draw() = 0;

	virtual void OnLoad() = 0;
	virtual void OnUnload() = 0;

protected:
	SDL_Renderer* ren;
	AudioPlayer* audio;
	KeyJoy* kj;
};

#endif