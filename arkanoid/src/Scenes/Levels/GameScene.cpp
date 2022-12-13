#include "GameScene.h"

GameScene::GameScene(SDL_Renderer* r, AudioPlayer* ap, KeyJoy* k)
	: Scene(r, ap, k)
{
	audio_hit_index = audio->addSoundEffect("assets/Effects/hit_paddle.mp3");
	audio_hit_brick_index = audio->addSoundEffect("assets/Effects/hit_brick.mp3");
	
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

	//bricks collision
	for (int i = 0, r; i < bricks.size(); i++)
	{
		r = bricks[i]->collides(ball->getRect());
		if (r != 0)
		{
			if (r == 1) // right
				ball->setXDir(1);
			if (r == 2) // bottom
				ball->setYDir(1);
			if (r == 3) // left
				ball->setXDir(-1);
			if (r == 4) // top
				ball->setYDir(-1);

			bricks.erase(bricks.begin() + i);
			audio->playSound(audio_hit_brick_index);
		}
	}

	// map borders
	if (ball->getLeftBound() < 22)
	{
		ball->setXDir(1); 
		//audio->playSound(audio_hit_brick_index);
	}
	if (ball->getRightBound() > 653)
	{
		ball->setXDir(-1); 
		//audio->playSound(audio_hit_brick_index);
	}
	if (ball->getTopBound() < 77) // 0x60px + 0x22px - 0x05
	{
		ball->setYDir(1); 
		//audio->playSound(audio_hit_brick_index);
	}

	// paddle interaction
	if (ball->getBottomBound() > paddle->getPos().y - 10 &&
		ball->getLeftBound() > paddle->getPos().x - 4 &&
		ball->getRightBound() < paddle->getPos().x + paddle->getWidth() + 4 &&
		ball->getTopBound() < paddle->getPos().y + paddle->getHeight())
	{
		ball->setYDir(-1);
		audio->playSound(audio_hit_index);
	}

	// lose 1 live
	if (ball->getBottomBound() > paddle->getPos().y + 200)
		ball->setPos(Vector2Int(300, 300));

	ball->update();
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
	ball->draw();

	for (Brick* b : bricks)
	{
		b->draw();
	}
}

void GameScene::OnLoad()
{
	Scene::OnLoad();

	paddle = new Player(ren, audio, kj);

	paddle->scale = .4f;
	paddle->setCenterPos();
	paddle->speed = 28; 
	paddle->setWidthLevel(.6f);

	ball = new Ball(ren);

	ball->setSpeed(10);
	ball->scale = .4f;
	ball->setPos(Vector2Int(300, 300));

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
	{
		bgno = 1;
		int arr[6][6] = {
			{ 0,  0,  0,  0,  0,  0},
			{ 1,  1,  1,  1,  1,  1},
			{ 2,  2,  2,  2,  1,  1},
			{-1, -1, -1, -1, -1, -1},
			{-1, -1, -1, -1, -1, -1},
			{-1, -1, -1, -1, -1, -1},
		};
		loadBricksByArr6x6(arr);
	}
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

void GameScene::loadBricksByArr6x6(int arr[6][6])
{
	int stx = 36;
	int sty = 130; 

	// map 6x6
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 6; x++)
		{
			if(arr[y][x] != -1)
				bricks.push_back(new Brick(ren, 1, 1, stx + x * 100, sty + y * 50, arr[y][x]));
		}
	}
}

Level::~Level()
{
	SDL_DestroyTexture(bg);
}
