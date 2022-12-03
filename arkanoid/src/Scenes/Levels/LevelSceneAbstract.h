#ifndef LEVEL_SCENE_MANAGER_H
#define LEVEL_SCENE_MANAGER_H

#include <SDL.h>
#include "../../SceneManager/Scene.h"

class LevelSceneManager : public Scene
{
public:
	LevelSceneManager(SDL_Renderer* r, AudioPlayer* ap, KeyJoy* k)
		: Scene(r, ap, k) { ; }

	virtual ~LevelSceneManager() { ; }

	virtual void update() = 0;
	virtual void events() { Scene::events(); };
	virtual void draw() = 0;

	virtual void OnLoad() = 0;
	virtual void OnUnload() = 0;
protected:

};

#endif