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
	/// Starting position where paddle have to be
	/// </summary>
	void setStartingPos(Vector2Int stpos);

	/// <summary>
	/// Set border where maximaly can player move paddle
	/// </summary>
	/// <param name="left"></param>
	/// <param name="right"></param>
	void setBorders(int left, int right);



	void events();
	void update();
	void draw();
private:
	SDL_Renderer* r;
	AudioPlayer* ap;
	KeyJoy* kj;
};

#endif