#ifndef OPTIONS_SCENE_H
#define OPTIONS_SCENE_H

#include "../../SceneManager/Scene.h"
#include "../../TextAsset/TextAsset.h"
#include "../../KeyJoy/KeyJoy.h"
#include "../../AudioPlayer/AudioPlayer.h"
#include "../../UISlider/UISlider.h"

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
	void changeOptionHor(int _new);
	void changeOptionVer(int _new);

protected:
	SDL_Texture* bg;
	Vector2Int mpos;
	FontAsset* font_hover_btn;
	FontAsset* font_def_btn;
	UISlider* slider;
	int moption; // current menu option
	int hoption; // current sldier option

	std::vector<TextAsset*> btns_txt;
	std::vector<UISlider*> option_sliders;

	bool active_first; // first page in opitons active
	bool active_nav_btns = false; // true if now controls back and arrows
	int n;
};

#endif