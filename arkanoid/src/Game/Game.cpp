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
	_setrunning(true);
}

int Game::_init_SDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return -1;

	Uint32 flags = SDL_WINDOW_SHOWN;

	win = SDL_CreateWindow("Arkanoid 2.0 WRBI",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		675, 780, flags);
	// 225x240 * 3 => 675x720 + 0x60
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
	eve = new SDL_Event();

	sman = new SceneManager(ren, eve);

	sman->addScene<MenuScene>();    // 0
	sman->addScene<OptionsScene>(); // 1

	sman->addScene<Lvl1Scene>();

	sman->loadScene(0);
	return 0;
}

Game::~Game()
{
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
}

void Game::run()
{
	while (_getrunning())
	{
		handleDef();

		while(SDL_PollEvent(eve))
			events();

		update();

		SDL_RenderClear(ren);
		draw();
		SDL_RenderPresent(ren);
	}
}

void Game::update()
{
	if (sceneReadyToLoad())
		sman->loadScene(getSceneToLoad());
	sman->update();
}

void Game::draw()
{
	sman->draw();
}

void Game::events()
{
	if (eve->type == SDL_QUIT || eve->type == SDL_KEYDOWN && eve->key.keysym.sym == SDLK_ESCAPE)
	{
		_setrunning(false);
	}

	sman->events();
}
