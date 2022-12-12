#ifndef PLAYER_H
#define PLAYER_H

#include "../TextureManager/TextureManager.h"
#include "../Vector2Int/Vector2Int.h"
#include "../AudioPlayer/AudioPlayer.h"
#include "../KeyJoy/KeyJoy.h"
#include <SDL.h>

class Player
{
public:
	Player(SDL_Renderer* r, AudioPlayer* ap, KeyJoy* kj);
	~Player();

	/// <summary>
	/// Set position
	/// </summary>
	void setPos(float stpos);
	Vector2Int getPos();
	int getWidth();
	int getHeight();

	void setCenterPos();

	/// <summary>
	/// Set border where maximaly can player move paddle
	/// </summary>
	/// <param name="left"></param>
	/// <param name="right"></param>
	void setBorders(int left, int right);

	/// <summary>
	/// Width of paddle
	/// </summary>
	/// <param name="lvl">value between 0 - 1</param>
	void setWidthLevel(float lvl);


	void events();
	void update();
	void draw();

	float scale;
	float speed;
private:
	SDL_Rect setRect(int x, int y, int w, int h);

	SDL_Renderer* r;
	AudioPlayer* audio;
	KeyJoy* kj;

	float movement;
	float xpos;
	int left_border, right_border;
	float wsize_lvl;

	SDL_Texture* body;

	SDL_Rect body_dstR;
	SDL_Rect body_srcR;
};

#endif