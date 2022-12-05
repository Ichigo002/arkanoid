#include "TextAsset.h"
#include "FontAsset.h"

TextAsset::TextAsset(FontAsset* asset)
{
	this->asset = asset;
	start_pos = Vector2Int(0, 0);
	spacing = 0;
	setText("Default Text");
}

TextAsset::TextAsset(FontAsset* asset, Vector2Int start_pos, int letter_spacing)
{
	this->asset = asset;
	this->start_pos = start_pos;
	spacing = letter_spacing;
	setText("Default Text");
}

TextAsset::TextAsset(FontAsset* asset, std::string txt)
{
	start_pos = Vector2Int(0, 0);
	spacing = 0;
	this->asset = asset;
	setText(txt);
}

TextAsset::~TextAsset()
{
}

void TextAsset::setText(std::string txt)
{
	this->txt = txt;
}

void TextAsset::setGraphicEffects(double angle, SDL_RendererFlip flip)
{
	this->angle = angle;
	this->flip = flip;
}

void TextAsset::setLetterSpacing(int s)
{
	spacing = s;
}

void TextAsset::setStartingPos(Vector2Int pos)
{
	start_pos = pos;
}

void TextAsset::setStartingPos(int x, int y)
{
	setStartingPos(Vector2Int(x, y));
}

void TextAsset::setNewFontAsset(FontAsset* f)
{
	asset = f;
}

void TextAsset::draw()
{
	SDL_Rect r;
	r.x = start_pos.x;
	r.y = start_pos.y;
	bool drawn = false;

	for (size_t i = 0; i < txt.length(); i++)
	{
		if (txt[i] == ' ')
		{
			SDL_QueryTexture(asset->__getglyphs()[0]->tex, nullptr, nullptr, &r.w, &r.h);
			r.x += r.w + spacing;
		}
		else
		{
			drawn = false;
			for (auto& obj : asset->__getglyphs())
			{
				if (obj->c == txt[i])
				{
					SDL_QueryTexture(obj->tex, nullptr, nullptr, &r.w, &r.h);
					SDL_RenderCopyEx(asset->__getren(), obj->tex, NULL, &r, angle, NULL, flip);
					r.x += r.w + spacing;
					drawn = true;
					break;
				}
			}
			if (!drawn)
			{
				SDL_QueryTexture(asset->__getglyphs()[0]->tex, nullptr, nullptr, &r.w, &r.h);
				SDL_RenderCopyEx(asset->__getren(), asset->__getglyphs()[0]->tex, NULL, &r, angle, NULL, flip);
				r.x += r.w + spacing;
			}
		}
		
	}
}
