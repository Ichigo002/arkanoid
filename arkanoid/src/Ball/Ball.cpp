#include "Ball.h"

Ball::Ball(SDL_Renderer* r)
	: r(r)
{
	tex = TextureManager::load(r, "assets/Texture/paddle_and_ball.png");

	srcR.x = 0;
	srcR.y = 44;
	srcR.w = 100;
	srcR.h = 99;

	scale = .3f;
	speed = 7;

	setXDir(-1);
	setYDir(-1);
}

Ball::~Ball()
{
}

void Ball::update()
{
	// set pos and scale for rect on the screen
	dstR.x += speed * dirx;
	dstR.y += speed * diry;
	dstR.w = srcR.w * scale;
	dstR.h = srcR.h * scale;
}

void Ball::draw()
{
	SDL_RenderCopy(r, tex, &srcR, &dstR);
}

void Ball::setPos(Vector2Int p)
{
	dstR.x = p.x;
	dstR.y = p.y;
}

void Ball::setSpeed(float v)
{
	speed = v;
}

float Ball::getXDir()
{
	return dirx;
}

float Ball::getYDir()
{
	return diry;
}

void Ball::setXDir(float d)
{
	dirx = d;
}

void Ball::setYDir(float d)
{
	diry = d;
}

SDL_Rect Ball::getRect()
{
	return dstR;
}

int Ball::getLeftBound()
{
	return dstR.x;
}

int Ball::getRightBound()
{
	return dstR.x + dstR.w;
}

int Ball::getTopBound()
{
	return dstR.y;
}

int Ball::getBottomBound()
{
	return dstR.y + dstR.h;
}
