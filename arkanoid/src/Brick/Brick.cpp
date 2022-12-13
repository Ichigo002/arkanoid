#include "Brick.h"

Brick::Brick(SDL_Renderer* r, float wsc, float hsc, int xpos, int ypos, int type)
	: r(r)
{
	// single brick: 100x50
	srcR = { 0, 0, 100, 50 };

	if (type > 4)
	{
		srcR.y = 50;
		srcR.x = 100 * (type - 5); // - 4 - 1
	}
	else
	{
		srcR.x = 100 * type;
		srcR.y = 0;
	}

	dstR = { xpos, ypos, int(srcR.w * wsc), int(srcR.h * hsc) };

	tex = TextureManager::load(r, "assets/Texture/bricks.png");
}

Brick::~Brick()
{
}

int Brick::collides(const SDL_Rect& r)
{
    //MTV (overlap) -> Penetretion Depth
    Vector2Int mtv(0, 0);
    Vector2Int proj, overlap;

    // test overlap in x axis
    proj.x = std::max(r.x + r.w, dstR.x + dstR.w) - std::min(r.x, dstR.x);
    if (proj.x < r.w + dstR.w)
    {
        overlap.x = r.w + dstR.w - proj.x;

        // test overlap in y axis
        proj.y = std::max(r.y + r.h, dstR.y + dstR.h) - std::min(r.y, dstR.y);
        if (proj.y < r.h + dstR.h)
        {
            //calculate mtv in y
            overlap.y = r.h + dstR.h - proj.y;
            //mtv.x = mtv.y = 0;

            //choose minimum overlap
            if (overlap.x < overlap.y)
            {
                mtv.x = overlap.x * (r.x < dstR.x ? -1 : 1);
                if (mtv.y > 0)
                    return 1;
                else
                    return 3;
            }
            else
            {
                mtv.y = overlap.y * (r.y < dstR.y ? -1 : 1);
                if (mtv.y > 0)
                    return 2;
                else
                    return 4;
            }
        }
    }
    return 0;
}

void Brick::draw()
{
	SDL_RenderCopy(r, tex, &srcR, &dstR);
}
