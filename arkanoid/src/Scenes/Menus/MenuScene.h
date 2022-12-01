#ifndef MENU_H
#define MENU_H

#include "../../SceneManager/Scene.h"
#include "../../TextAsset/TextAsset.h"
#include "../../KeyJoy/KeyJoy.h"

class MenuScene : public Scene
{
public:
	MenuScene(SDL_Renderer* r, SDL_Event* e);
	~MenuScene();

	virtual void update();
	virtual void events();
	virtual void draw();

	virtual void OnLoad();
	virtual void OnUnload();

protected:
	FontAsset* font;
	TextAsset* txt;

	KeyJoy* kj;
};

#endif