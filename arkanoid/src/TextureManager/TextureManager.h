#ifndef TEXUTRE_MANAGER_H
#define TEXUTRE_MANAGER_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>

class TextureManager
{
public:
	static SDL_Texture* load(SDL_Renderer* r, std::string filename)
	{
		SDL_Surface* srf = IMG_Load(filename.c_str());
		return SDL_CreateTextureFromSurface(r, srf);
	}
};

#endif