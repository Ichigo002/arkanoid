#ifndef LVL1_H
#define LVL1_H

#include "LevelSceneAbstract.h"

class Lvl1Scene : public LevelSceneManager
{
public:
	Lvl1Scene(SDL_Renderer* r, AudioPlayer* ap, KeyJoy* k);

	virtual ~Lvl1Scene();

	virtual void update();
	virtual void events();
	virtual void draw();

	virtual void OnLoad();
	virtual void OnUnload();

protected:

};

#endif