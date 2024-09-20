#include "WinScene.h"
#include "../../Game/Running.h"

WinScene::WinScene(SDL_Renderer* r, AudioPlayer* ap, KeyJoy* k)
	: Scene(r, ap, k)
{
	SDL_Color c = { 255, 255, 255 };
	font_def = new FontAsset(r, "assets/Fonts/Pixelmania.ttf", 30, c);
	c = { 244, 32, 32 };
	font_hover = new FontAsset(r, "assets/Fonts/Pixelmania.ttf", 30, c);

	point_txt = new TextAsset(font_def);
	point_txt->setStartingPos(70, 550);

	txts.push_back(new TextAsset(font_def, "PLAY AGAIN"));
	txts[txts.size() - 1]->setStartingPos(130, 640);

	txts.push_back(new TextAsset(font_def, "BACK MENU"));
	txts[txts.size() - 1]->setStartingPos(140, 714);

	audio->addSoundEffect("assets/Effects/button_select.mp3");
	audio->addSoundEffect("assets/Effects/button_clicked.mp3");

	bg = TextureManager::load(r, "assets/Texture/bg_win2.png");
	changeOption(0);
}

WinScene::~WinScene()
{
}

void WinScene::update()
{
	Scene::update();
	//txts[0]->setStartingPos(mpos);
}

void WinScene::events()
{
	Scene::events();
	//DEVELOPER
	if (kj->getAction_Accept())
	{
		std::cout << "Item pos: " << mpos << std::endl;
	}

	if (kj->getEventData()->type == SDL_MOUSEMOTION)
	{
		mpos.x = kj->getEventData()->button.x;
		mpos.y = kj->getEventData()->button.y;
	}
	// --------

	if (kj->getAction_Next())
	{
		audio->playSound(0);
		changeOption(moption + 1);
	}

	if (kj->getAction_Prev())
	{
		audio->playSound(0);
		changeOption(moption - 1);
	}

	// LOADING
	if (kj->getAction_Accept())
	{
		audio->playSound(1);
		switch (moption)
		{
		case 0:
			loadScene(2);
			break;
		case 1:
			loadScene(0);
			break;
		}
	}
}

void WinScene::draw()
{
	SDL_RenderCopy(ren, bg, NULL, NULL);

	point_txt->draw();

	Scene::draw();
}

void WinScene::OnLoad()
{
	Scene::OnLoad();
	std::string tmp_txt = "SCORE IS " + std::to_string(audio->__total_points__);
	point_txt->setText(tmp_txt);
}

void WinScene::OnUnload()
{
	Scene::OnUnload();
}

void WinScene::changeOption(int _new)
{
	if (_new < 0)
		_new = txts.size() - 1;
	else if (_new >= txts.size())
		_new = 0;

	txts[moption]->setNewFontAsset(font_def);
	txts[_new]->setNewFontAsset(font_hover);

	moption = _new;
}
