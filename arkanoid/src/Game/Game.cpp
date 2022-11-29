#include "Game.h"

Game::Game()
{
	int r;
	r = _init_SDL();
	if (r != 0)
	{
		throwError(__FUNCTION__, "Error init SDL. System error: " + std::to_string(r));
		return;
	}
	r = _init_objects();
	if (r != 0)
	{
		throwError(__FUNCTION__, "Error init SDL. System error: " + std::to_string(r));
		return;
	}
	running = true;
}

int Game::_init_SDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return -1;

	Uint32 flags = SDL_WINDOW_SHOWN;

	win = SDL_CreateWindow("Arkanoid 2.0 WRBI",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		675, 720, flags);
	// 225x240 * 3 => 675x720
	if (win == NULL)
		return -2;

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);

	if (ren == NULL)
		return -3;

	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

	return 0;
}

int Game::_init_objects()
{
	SDL_Color col = { 255, 255, 0 };
	font = new FontAsset(ren, "assets/fonts/prstart.ttf", 25, col);

	txt = new TextAsset(font, "To jest testowy napis");

	eve = new SDL_Event();
	return 0;
}

Game::~Game()
{
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
}

void Game::run()
{
	while (running)
	{
		events();
		update();

		SDL_RenderClear(ren);
		draw();
		SDL_RenderPresent(ren);
	}
}

void Game::update()
{

}

void Game::draw()
{
	txt->draw();
}

void Game::events()
{
	SDL_PollEvent(eve);

	if (eve->type == SDL_QUIT || eve->type == SDL_KEYDOWN && eve->key.keysym.sym == SDLK_ESCAPE)
	{
		running = false;
	}
}
