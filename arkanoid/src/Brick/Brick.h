#ifndef BRICK_H
#define BRICK_H

#include <SDL.h>
#include "../TextureManager/TextureManager.h"
#include "../Vector2Int/Vector2Int.h"

class Brick
{
public:
	/// <param name="r">renderer</param>
	/// <param name="wsc">width scale</param>
	/// <param name="hsc">height scale</param>
	/// <param name="xpos">x position</param>
	/// <param name="ypos">y position</param>
	/// <param name="type">type of block color: 0 - 6</param>
	Brick(SDL_Renderer* r, float wsc, float hsc, int xpos, int ypos, int type);
	~Brick();

	/// <summary>
	/// If rect collides with brick then return value not equl 0
	/// </summary>
	/// <param name="r"></param>
	/// <returns>
	/// 0 - no collides
	/// 1 - right collision
	/// 2 - bottom collision
	/// 3 - left collision
	/// 4 - top collision
	/// </returns>
	int collides(const SDL_Rect& r);

	void draw();

protected:
	SDL_Renderer* r;
	SDL_Texture* tex;
	SDL_Rect srcR, dstR;
};

#endif