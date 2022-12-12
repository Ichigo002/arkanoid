#include "Ball.h"

Ball::Ball(SDL_Renderer* r, AudioPlayer* ap)
	: r(r), audio(ap)
{
	tex = TextureManager::load(r, "assets/Texture/paddle_and_ball.png");

	srcR.x = 0;
	srcR.y = 44;
	srcR.w = 100;
	srcR.h = 99;

	scale = .5f;
	speed = 4;
}

Ball::~Ball()
{
}

void Ball::update()
{
	// set pos and scale for rect on the screen
	dstR.x += speed * dir.x;
	dstR.y += speed * dir.y;
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

void Ball::setXDir(int d)
{
	dir.x = d;
}

void Ball::setYDir(int d)
{
	dir.y = d;
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
