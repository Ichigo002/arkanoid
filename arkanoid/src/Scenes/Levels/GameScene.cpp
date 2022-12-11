#include "GameScene.h"

GameScene::GameScene(SDL_Renderer* r, AudioPlayer* ap, KeyJoy* k)
	: Scene(r, ap, k)
{
	// size: 675x720 + 0x10
	// pos: 0x50
	lvl_bg_dstR.x = 0;
	lvl_bg_dstR.y = 50;
	lvl_bg_dstR.w = 675;
	lvl_bg_dstR.h = 730;
}

GameScene::~GameScene()
{
}

void GameScene::update()
{
	Scene::update();
	paddle->update();
}

void GameScene::events()
{
	Scene::events();
	paddle->events();
}

void GameScene::draw()
{
	Scene::draw();

	if (!current_lvl)
		return;

	SDL_RenderCopy(ren, current_lvl->bg, NULL, &lvl_bg_dstR);
	paddle->draw();
}

void GameScene::OnLoad()
{
	Scene::OnLoad();

	paddle = new Player(ren, audio, kj);

	curr_index_lvl = 0;
	loadLvl(curr_index_lvl);
}

void GameScene::OnUnload()
{
	Scene::OnUnload();
	unloadLvl();
}

void GameScene::loadLvl(int lvl)
{
	Level* l = new Level();

	int bgno = 0; // Bg to load for lvl

	// Every case is single level
	switch (lvl)
	{
	case 0:
		bgno = 3;
		break;
	default:
		return;
	}

	l->bg = TextureManager::load(ren, "assets/Texture/levels_bg/bg-" + std::to_string(bgno) + ".png");

	current_lvl = l;
}

void GameScene::unloadLvl()
{
	current_lvl = nullptr;
}

Level::~Level()
{
	SDL_DestroyTexture(bg);
}
