#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include "../AudioPlayer/AudioPlayer.h"
#include "../KeyJoy/KeyJoy.h"
#include "../TextureManager/TextureManager.h"

class Ball
{
public:
	Ball(SDL_Renderer* r, AudioPlayer* ap, KeyJoy* kj);
	~Ball();
private:
	SDL_Renderer* r;
	AudioPlayer* audio;
	KeyJoy* kj;
};

#endif