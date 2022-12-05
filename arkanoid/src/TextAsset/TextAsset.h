#ifndef TEXT_ASSET_H
#define TEXT_ASSET_H

#include <SDL.h>
#include "FontAsset.h"
#include "../Vector2Int/Vector2Int.h"

class TextAsset
{
public:
	TextAsset(FontAsset* asset);
	TextAsset(FontAsset* asset, Vector2Int start_pos, int letter_spacing);
	TextAsset(FontAsset* asset, std::string txt);
	~TextAsset();

	/// <summary>
	/// Set Text to render
	/// </summary>
	/// <param name="txt">text message</param>
	void setText(std::string txt);

	void setGraphicEffects(double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

	/// <summary>
	/// Space between single letters
	/// </summary>
	/// <param name="s"></param>
	void setLetterSpacing(int s);

	/// <summary>
	/// Starting position on the screen
	/// </summary>
	void setStartingPos(Vector2Int pos);
	void setStartingPos(int x, int y);

	/// <summary>
	/// Sets new font asset to render
	/// </summary>
	void setNewFontAsset(FontAsset* f);

	/// <summary>
	/// Draw the text
	/// </summary>
	void draw();

private:
	FontAsset* asset;
	std::string txt;
	Vector2Int start_pos;
	int spacing;
	double angle;
	SDL_RendererFlip flip;
};

#endif
