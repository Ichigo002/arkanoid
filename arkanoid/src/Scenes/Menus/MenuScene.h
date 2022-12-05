#ifndef MENU_H
#define MENU_H

#include "../../SceneManager/Scene.h"
#include "../../TextAsset/TextAsset.h"
#include "../../KeyJoy/KeyJoy.h"
#include "../../AudioPlayer/AudioPlayer.h"

class MenuScene : public Scene
{
public:
	MenuScene(SDL_Renderer* r, AudioPlayer* ap, KeyJoy* k);
	~MenuScene();

	virtual void update();
	virtual void events();
	virtual void draw();

	virtual void OnLoad();
	virtual void OnUnload();

protected:
	void changeOption(int _new);

protected:
	SDL_Texture* bg;
	Vector2Int mpos;
	FontAsset* font_hover;
	int moption; // current menu option
};

#endif