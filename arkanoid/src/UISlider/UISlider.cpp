#include "UISlider.h"

UISlider::UISlider(SDL_Renderer* r, AudioPlayer* ap, KeyJoy* k)
	: ren(r), audio(ap), kj(k)
{
	bg = TextureManager::load(ren, "assets/Texture/UISlider/bg.png");
	slider = TextureManager::load(ren, "assets/Texture/UISlider/slider.png");
	handle = TextureManager::load(ren, "assets/Texture/UISlider/handle.png");
	handle_hover = TextureManager::load(ren, "assets/Texture/UISlider/handle_hover.png");

	SDL_QueryTexture(slider, NULL, NULL, &slider_dstR.w, &slider_dstR.h);
	SDL_QueryTexture(handle, NULL, NULL, &handle_dstR.w, &handle_dstR.h);
	SDL_QueryTexture(handle_hover, NULL, NULL, &handle_dstR.w, &handle_dstR.h);

	// Default values obviously
	setPos(Vector2Int(100, 100));
	setSize(Vector2Int(300, 100));

}

UISlider::~UISlider()
{
}

void UISlider::draw()
{
	SDL_RenderCopy(ren, bg, NULL, &bg_dstR);
	SDL_RenderCopy(ren, slider, NULL, &slider_dstR);

	if(is_hover)
		SDL_RenderCopy(ren, handle_hover, NULL, &handle_dstR);
	else
		SDL_RenderCopy(ren, handle, NULL, &handle_dstR);

}

void UISlider::events()
{
	if (!is_hover)
		return;

}

void UISlider::update()
{
	//All
	bg_dstR.x = slider_dstR.x = handle_dstR.x = rpos.x;
	bg_dstR.y = slider_dstR.y = handle_dstR.y = rpos.y;
	//Bg
	bg_dstR.w = rsize.x; // bg size
	bg_dstR.h = rsize.y; // bg size
	//Slider
	slider_dstR.w = rsize.x * .9f;  // scaled size of slider
	slider_dstR.h = rsize.y * .12f; // scaled size of slider
	slider_dstR.y += rsize.y / 2 - slider_dstR.h / 2;
	slider_dstR.x += (rsize.x - slider_dstR.w) / 2;
	//Handle
	handle_dstR.w = handle_dstR.h = 40; // size of handle

	handle_dstR.y += rsize.y / 2 - handle_dstR.h / 2;
	handle_dstR.x += (rsize.x - handle_dstR.w) * value;
}

void UISlider::focus()
{
	is_hover = true;
}

void UISlider::unfocus()
{
	is_hover = false;
}

void UISlider::increaseValue()
{
	value += prec;
	if (value > 1)
		value = 1;
}

void UISlider::decreaseValue()
{
	value -= prec;
	if (value < 0)
		value = 0;
}

void UISlider::setPrecision(float p)
{
	if(p > 0 && p <= 1.0f)
		prec = p;
}

float UISlider::getValue()
{
	return value;
}

void UISlider::setPos(Vector2Int p)
{
	rpos = p;
}

void UISlider::setSize(Vector2Int size)
{
	rsize = size;
}

Vector2Int UISlider::getSize()
{
	return rsize;
}

Vector2Int UISlider::getPos()
{
	return rpos;
}
