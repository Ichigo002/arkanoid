#include "Ball.h"

Ball::Ball(SDL_Renderer* r, AudioPlayer* ap)
	: r(r), audio(ap)
{
	tex = TextureManager::load(r, "assets/Texture/paddle_and_ball.png");

	srcR.x = 0;
	srcR.y = 44;
	srcR.w = 100;
	srcR.h = 99;
	scale = 1;
	pos.set(100, 100);
}

Ball::~Ball()
{
}

void Ball::update()
{
	// set pos and scale for rect on the screen
	dstR.x = pos.x;
	dstR.y = pos.y;
	dstR.w = srcR.w * scale;
	dstR.h = srcR.h * scale;
}

void Ball::draw()
{
	SDL_RenderCopy(r, tex, &srcR, &dstR);
}

void Ball::setPos(Vector2Int p)
{
	pos = p;
}

void Ball::setSpeed(float v)
{
	speed = v;
}
