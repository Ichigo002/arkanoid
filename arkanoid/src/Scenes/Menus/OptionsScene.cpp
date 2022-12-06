#include "OptionsScene.h"

// TODO 6 Make event void OnFirstLoad() to all scenes to use less memory
OptionsScene::OptionsScene(SDL_Renderer* r, AudioPlayer* ap, KeyJoy* k)
	: Scene(r, ap, k)
{
	SDL_Color c = { 255, 255, 255 };
	font_def = new FontAsset(r, "assets/Fonts/pixel font-7.ttf", 25, c);
	font_def_btn = new FontAsset(r, "assets/Fonts/pixel font-7.ttf", 70, c);
	c = { 244, 32, 32 };
	font_hover_btn = new FontAsset(r, "assets/Fonts/pixel font-7.ttf", 70, c);


	//FIRST PAGE

	txts.push_back(new TextAsset(font_def, ""));
	txts[txts.size() - 1]->setStartingPos(250, 500);

	//=====================

	btns_txt.push_back(new TextAsset(font_def_btn, "->"));
	btns_txt[btns_txt.size() - 1]->setStartingPos(592, 703);

	btns_txt.push_back(new TextAsset(font_def_btn, "BACK"));
	btns_txt[btns_txt.size() - 1]->setStartingPos(270, 703);

	btns_txt.push_back(new TextAsset(font_def_btn, "<-"));
	btns_txt[btns_txt.size() - 1]->setStartingPos(18, 703);

	audio->addSoundEffect("assets/Effects/button_select.mp3");
	audio->addSoundEffect("assets/Effects/button_clicked.mp3");

	bg = TextureManager::load(r, "assets/Texture/bg_menu.png");

	active_first = true;
	changeOption(1);
}

OptionsScene::~OptionsScene()
{
}

void OptionsScene::update()
{
	Scene::update();
	//txts[0]->setStartingPos(mpos);
}

void OptionsScene::events()
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

	if (kj->getAction_Prev_Hor())
	{
		audio->playSound(0);
		changeOption(moption + 1);
	}

	if (kj->getAction_Next_Hor())
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
			active_first = false;
			changeOption(2);
			break;
		case 1:
			loadScene(0);
			break;
		case 2:
			active_first = true;
			changeOption(0);
			break;
		}
	}
}

void OptionsScene::draw()
{
	SDL_RenderCopy(ren, bg, NULL, NULL);

	if(active_first)
		Scene::draw();

	if (active_first)
		btns_txt[0]->draw();
	btns_txt[1]->draw();
	if (!active_first)
		btns_txt[2]->draw();
}

void OptionsScene::OnLoad()
{
	Scene::OnLoad();
}

void OptionsScene::OnUnload()
{
	Scene::OnUnload();
}

void OptionsScene::changeOption(int _new)
{
	if (_new < (active_first ? 0 : 1))
		_new = btns_txt.size() - (active_first ? 2 : 1);
	else if (_new >= (active_first ? btns_txt.size() - 1 : btns_txt.size()))
		_new = (active_first ? 0 : 1);

	btns_txt[moption]->setNewFontAsset(font_def_btn);
	btns_txt[_new]->setNewFontAsset(font_hover_btn);

	moption = _new;
}
