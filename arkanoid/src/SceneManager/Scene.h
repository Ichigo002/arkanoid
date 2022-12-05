#ifndef LEVEL_SCENE_ABSTRACT_H
#define LEVEL_SCENE_ABSTRACT_H

#include <SDL.h>
#include "../AudioPlayer/AudioPlayer.h"
#include "../KeyJoy/KeyJoy.h"
#include "../TextAsset/TextAsset.h"
#include "../TextureManager/TextureManager.h"
#include <vector>
#include "SceneChanger.h"

class Scene
{
public:
	Scene(SDL_Renderer* r, AudioPlayer* ap, KeyJoy* k)
		: ren(r), audio(ap), kj(k) { 
		SDL_Color c = { 255, 0 , 0 };
		font_def = new FontAsset(r, "assets/Fonts/prstart.ttf", 35, c);
	}
	virtual ~Scene() { ; }

	virtual void update() { ; };

	virtual void events() { 
		kj->events(); 
	}

	virtual void draw() { 
		for (TextAsset* t : txts)
			t->draw();
	}

	virtual void OnLoad() { ; };
	virtual void OnUnload() { ; };

protected:
	SDL_Renderer* ren;
	AudioPlayer* audio;
	KeyJoy* kj;

	std::vector<TextAsset*> txts;
	FontAsset* font_def; // default font
};

#endif