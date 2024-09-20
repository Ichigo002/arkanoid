#ifndef WIN_SCENE_H
#define WIN_SCENE_H

#include "../../SceneManager/Scene.h"
#include "../../TextAsset/TextAsset.h"
#include "../../KeyJoy/KeyJoy.h"
#include "../../AudioPlayer/AudioPlayer.h"

class WinScene : public Scene
{
public:
	WinScene(SDL_Renderer* r, AudioPlayer* ap, KeyJoy* k);
	~WinScene();

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
	TextAsset* point_txt;
	int moption; // current menu option
};

#endif