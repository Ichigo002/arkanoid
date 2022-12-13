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
	Ball(SDL_Renderer* r);
	~Ball();

	void update();
	void draw();

	void setPos(Vector2Int p);
	void setSpeed(float v);

	/// <summary>
	/// set Direction of falling ball
	/// </summary>
	/// <param name="d">available values axis: -1; 1</param>
	void setXDir(int d);

	/// <summary>
	/// set Direction of falling ball
	/// </summary>
	/// <param name="d">available values axis: -1; 1</param>
	void setYDir(int d);

	SDL_Rect getRect();

	int getLeftBound();
	int getRightBound();
	int getTopBound();
	int getBottomBound();

	float scale;
private:
	SDL_Renderer* r;
	int au_index;

	float speed;
	Vector2Int dir;
	SDL_Rect srcR, dstR;
	SDL_Texture* tex;
};

#endif