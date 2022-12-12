#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include "../AudioPlayer/AudioPlayer.h"
#include "../KeyJoy/KeyJoy.h"
#include "../Vector2Int/Vector2Int.h"
#include "../TextureManager/TextureManager.h"

class Ball
{
public:
	Ball(SDL_Renderer* r, AudioPlayer* ap);
	~Ball();

	void update();
	void draw();

	void setPos(Vector2Int p);
	void setSpeed(float v);

	float scale;
private:
	SDL_Renderer* r;
	AudioPlayer* audio;

	Vector2Int pos;
	float speed;
	SDL_Rect srcR, dstR;
	SDL_Texture* tex;
};

#endif