#ifndef OPTIONS_SCENE_H
#define OPTIONS_SCENE_H

#include "../../SceneManager/Scene.h"
#include "../../TextAsset/TextAsset.h"
#include "../../KeyJoy/KeyJoy.h"
#include "../../AudioPlayer/AudioPlayer.h"

class OptionsScene : public Scene
{
public:
	OptionsScene(SDL_Renderer* r, AudioPlayer* ap, KeyJoy* k);
	~OptionsScene();

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
	FontAsset* font_hover_btn;
	FontAsset* font_def_btn;
	int moption; // current menu option

	std::vector<TextAsset*> btns_txt;

	bool active_first; // first page in opitons active
};

#endif