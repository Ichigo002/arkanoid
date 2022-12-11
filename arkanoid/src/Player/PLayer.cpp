#include "Player.h"

Player::Player(SDL_Renderer* r, AudioPlayer* ap, KeyJoy* kj)
	: r(r), audio(ap), kj(kj)
{
	body = TextureManager::load(r, "assets/Texture/paddle_and_ball.png");

	body_dstR.y = 650;

	scale = .5f;
	speed = 11;

	setWidthLevel(.75f);
	setBorders(22, 653); // DEF: 0x675
	setCenterPos();
}

Player::~Player()
{
}

void Player::setPos(float stpos)
{
	xpos = stpos;
}

void Player::setCenterPos()
{
	xpos = (right_border - left_border) / 2 + left_border - (107 * scale + 400 * scale * wsize_lvl) / 2 + 20; // + 20. static unknown value
}

void Player::setBorders(int left, int right)
{
	left_border = left;
	right_border = right;
}

void Player::setWidthLevel(float lvl)
{
	wsize_lvl = lvl;
}

void Player::events()
{
	movement = kj->getAction_MoveLR();
}

void Player::update()
{
	xpos += movement * speed;

	if (xpos < left_border)
		xpos = left_border;
	if (xpos + (107 * scale + 400 * scale * wsize_lvl-25) > right_border)
		xpos = right_border - (107 * scale + 400 * scale * wsize_lvl-25);
}

void Player::draw()
{

	// left edge:  51x44
	body_srcR = setRect(0, 0, 51, 44);
	body_dstR = setRect(xpos, body_dstR.y, body_srcR.w * scale, body_srcR.h * scale);

	SDL_RenderCopy(r, body, &body_srcR, &body_dstR);

	// center:     400x44
	body_srcR = setRect(body_srcR.x + body_srcR.w, body_srcR.y, 400, body_srcR.h);
	body_dstR = setRect(xpos + body_dstR.w, body_dstR.y, body_srcR.w * scale * wsize_lvl, body_srcR.h * scale);

	SDL_RenderCopy(r, body, &body_srcR, &body_dstR);

	// right edge: 56x44
	body_srcR = setRect(body_srcR.x + body_srcR.w, body_srcR.y, 56, body_srcR.h);
	body_dstR = setRect(xpos + body_dstR.w, body_dstR.y, body_srcR.w * scale, body_srcR.h * scale);

	SDL_RenderCopy(r, body, &body_srcR, &body_dstR);
}

SDL_Rect Player::setRect(int x, int y, int w, int h)
{
	SDL_Rect r = { x,y,w,h };
	return r;
}
