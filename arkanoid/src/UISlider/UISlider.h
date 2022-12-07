#ifndef UISLIDER_H
#define UISLIDER_H

#include <SDL.h>
#include "../KeyJoy/KeyJoy.h"
#include "../AudioPlayer/AudioPlayer.h"
#include "../TextureManager/TextureManager.h"
#include "../Vector2Int/Vector2Int.h"

class UISlider
{
public:
	UISlider(SDL_Renderer* r, AudioPlayer* ap, KeyJoy* k);
	~UISlider();

	void draw();
	void events();
	void update();

	void focus();
	void unfocus();

	float value; // value between 0.0f - 1.0f

	void setPos(Vector2Int p);
	// render size in pixels x = width, y = height
	void setSize(Vector2Int size);

	Vector2Int getSize();
	Vector2Int getPos();

protected:
	KeyJoy* kj;
	AudioPlayer* audio;
	SDL_Renderer* ren;

	Vector2Int rpos; // render position
	Vector2Int rsize; // render size in pixels x = width, y = height

	SDL_Texture* bg;
	SDL_Texture* slider;
	SDL_Texture* handle;
	SDL_Texture* handle_hover;

	SDL_Rect bg_dstR;
	SDL_Rect slider_dstR;
	SDL_Rect handle_dstR;

	bool is_hover;
};

#endif