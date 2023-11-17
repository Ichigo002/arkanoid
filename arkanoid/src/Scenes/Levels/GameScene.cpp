#include "GameScene.h"

GameScene::GameScene(SDL_Renderer* r, AudioPlayer* ap, KeyJoy* k)
	: Scene(r, ap, k)
{
	audio_hit_index = audio->addSoundEffect("assets/Effects/hit_paddle.mp3");
	audio_hit_brick_index = audio->addSoundEffect("assets/Effects/hit_brick.mp3");
	
	SDL_Color c = { 255, 0, 0 };
	font_def = new FontAsset(r, "assets/Fonts/prstart.ttf", 26, c);

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

	updateBricks();
	updateMapBorders();
	updatePaddle();
	updateLogic();
	updateCounters();
	 
	ball->update();
}

void GameScene::updateBricks()
{
	//bricks collision
	for (int i = 0, r; i < bricks.size(); i++)
	{
		r = bricks[i]->collides(ball->getRect());
		if (r != 0)
		{
			if (r == 1) // right
				ball->setXDir(-ball->getXDir());
			if (r == 2) // bottom
				ball->setYDir(-ball->getYDir());
			if (r == 3) // left
				ball->setXDir(-ball->getXDir());
			if (r == 4) // top
				ball->setYDir(-ball->getYDir());

			combo_counter++;

			points += (bricks[i]->getType() + 1) * hit_points / (paddle->scale * 3);

			if (combo_counter != 0)
				points += (combo_counter - 1) * hit_points / 2;


			bricks.erase(bricks.begin() + i);
			audio->playSound(audio_hit_brick_index);
		}
	}

}

void GameScene::updatePaddle()
{
	// paddle interaction
	if (ball->getBottomBound() > paddle->getPos().y - 10 &&
		ball->getLeftBound() > paddle->getPos().x - 4 &&
		ball->getRightBound() < paddle->getPos().x + paddle->getWidth() + 4 &&
		ball->getTopBound() < paddle->getPos().y + paddle->getHeight())
	{
		combo_counter = 0;
		ball->setYDir(-1);
		audio->playSound(audio_hit_index);
	}
	paddle->update();
}

void GameScene::updateMapBorders()
{
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

}

void GameScene::updateLogic()
{
	// lose 1 live
	if (ball->getBottomBound() > paddle->getPos().y + 200)
	{
		lives--;
		ball->setPos(Vector2Int(300, 460));
		float v;
		do
		{
			v = ((rand() % 201) - 100.0f) / 100.0f;
		} while (v < .17f && v > -.17f);

		ball->setXDir(v);
		
		if (lives == 0)
		{
			//you loser
			loadScene(3);
		}
	}
	// win this lvl
	if (bricks.size() == 0)
	{
		curr_index_lvl++;
		loadLvl(curr_index_lvl);
	}
}

void GameScene::updateCounters()
{
	// protecting
	if (points > 99'999)
	{
		points = 0;
		std::cout << "!! Maximal score reached. Reset counter !!" << std::endl;
	}

	txts[0]->setText("Lives: " + std::to_string(lives));
	std::string tmp = std::to_string(points);
	std::string tmpn = "";
	for (int i = 0; i < 5 - tmp.length(); i++)
	{
		tmpn += "0";
	}
	txts[1]->setText("Score: " + tmpn + tmp);
}

void GameScene::events()
{
	Scene::events();
	paddle->events();
	if (kj->getEventData()->type == SDL_MOUSEMOTION)
	{
		mpos.set(kj->getEventData()->button.x, kj->getEventData()->button.y);
	}
	if (kj->getAction_Accept())
	{
		std::cout << mpos << std::endl;
	}
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
	ball = new Ball(ren);


	paddle->speed = audio->__control_sensitivity_option__ * 28 * 2;

	int txi = 0;

	txts.push_back(new TextAsset(font_def));
	txts[txi]->setStartingPos(Vector2Int(8, 13));
	txi++;

	txts.push_back(new TextAsset(font_def));
	txts[txi]->setStartingPos(Vector2Int(353, 13));
	txi++;

	lives = 3;
	points = 0;

	curr_index_lvl = 0;
	loadLvl(curr_index_lvl);
}

void GameScene::OnUnload()
{
	Scene::OnUnload();
	txts.clear();
	unloadLvl();
}

void GameScene::loadLvl(int lvl)
{
	Level* l = new Level();

	int bgno = 0; // Bg to load for lvl

	ball->scale = .4f;
	ball->setPos(Vector2Int(300, 460));
	ball->setYDir(1);
	float v;
	do
	{
		v = ((rand() % 201) - 100.0f) / 100.0f;
	} while (v < .17f && v > -.17f);

	ball->setXDir(v);
	hit_points = 100;
	combo_counter = 0;

	paddle->setCenterPos();
	paddle->scale = .4f;


	// Every case is single level
	switch (lvl)
	{
	case 0:
	{
		hit_points = 70;
		paddle->setWidthLevel(1);
		ball->setSpeed(8);

		bgno = 2; // background
		int arr[6][6] = {
			{ 0,  0,  0,  0,  0,  0},
			{ 0,  0,  0,  0,  0,  0},
			{ 0,  0,  0,  0,  0,  0},
			{ 0,  0,  0,  0,  0,  0},
			{ 0,  0,  0,  0,  0,  0},
			{ 0,  0,  0,  0,  0,  0},
		};
		loadBricksByArr6x6(arr);
	}
	break;

	case 1:
	{
		hit_points = 100;
		paddle->setWidthLevel(.6f);
		ball->setSpeed(8);

		bgno = 0; // background
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

	default: // Win scene loading later
		loadScene(1);
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
