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

	// FIRST PAGE

	option_sliders.push_back(new UISlider( r, ap, k));
	option_sliders[0]->setPos(Vector2Int(100, 100));
	option_sliders.push_back(new UISlider( r, ap, k));
	option_sliders[1]->setPos(Vector2Int(100, 300));
	option_sliders.push_back(new UISlider( r, ap, k));
	option_sliders[2]->setPos(Vector2Int(100, 500));


	//SECOND PAGE

	txts.push_back(new TextAsset(font_def, "In game"));
	txts[txts.size() - 1]->setStartingPos(559, 258);
	txts.push_back(new TextAsset(font_def, "you must move"));
	txts[txts.size() - 1]->setStartingPos(500, 300);
	txts.push_back(new TextAsset(font_def, "a paddle to bounce"));
	txts[txts.size() - 1]->setStartingPos(450, 337);
	txts.push_back(new TextAsset(font_def, "falling ball."));
	txts[txts.size() - 1]->setStartingPos(423, 373);
	txts.push_back(new TextAsset(font_def, "Ball hits bricks and destroy its."));
	txts[txts.size() - 1]->setStartingPos(300, 425);
	txts.push_back(new TextAsset(font_def, "If you successfully destroy all bricks,"));
	txts[txts.size() - 1]->setStartingPos(215, 460);
	txts.push_back(new TextAsset(font_def, "you will obviously pass to next level."));
	txts[txts.size() - 1]->setStartingPos(196, 491);

	txts.push_back(new TextAsset(font_def, "CONTROLLER ; KEYBOARD => action"));
	txts[txts.size() - 1]->setStartingPos(8, 533);

	txts.push_back(new TextAsset(font_def, "X axis ; A,D ; LEFT-RIGHT ARROW => moves paddle"));
	txts[txts.size() - 1]->setStartingPos(8, 560);
	txts.push_back(new TextAsset(font_def, "Back ; Escape => pause/unpause game"));
	txts[txts.size() - 1]->setStartingPos(8, 596);
	txts.push_back(new TextAsset(font_def, "A on gamepad; Enter => clicks button"));
	txts[txts.size() - 1]->setStartingPos(8, 630);

	//=====================

	btns_txt.push_back(new TextAsset(font_def_btn, "->"));
	btns_txt[btns_txt.size() - 1]->setStartingPos(592, 703);

	btns_txt.push_back(new TextAsset(font_def_btn, "BACK"));
	btns_txt[btns_txt.size() - 1]->setStartingPos(270, 703);

	btns_txt.push_back(new TextAsset(font_def_btn, "<-"));
	btns_txt[btns_txt.size() - 1]->setStartingPos(18, 703);

	bg = TextureManager::load(r, "assets/Texture/bg_menu.png");

	active_first = true;
	changeOptionHor(1);
	n = 7;
}

OptionsScene::~OptionsScene()
{
}

void OptionsScene::update()
{
	Scene::update();
	for (UISlider* s : option_sliders)
	{
		s->update();
	}

	//txts[n]->setStartingPos(mpos);
}

void OptionsScene::events()
{
	Scene::events();
	for (UISlider* s : option_sliders)
	{
		s->events();
	}

	//DEVELOPER
	if (kj->getPressedKey(SDLK_j))
	{
		if(n < txts.size()-1)
			n++;
		std::cout << "Item pos: " << mpos << std::endl;

		std::cout << "Option sldiers size: " << option_sliders.size() << std::endl;
	}

	if (kj->getEventData()->type == SDL_MOUSEMOTION)
	{
		mpos.x = kj->getEventData()->button.x;
		mpos.y = kj->getEventData()->button.y;
	}
	// --------

	if (kj->getAction_Prev_Hor())
	{
		if (!active_nav_btns)
		{
			option_sliders[hoption]->decreaseValue();
		}
		else
		{
			audio->playSound(0);
			changeOptionHor(moption + 1);
		}
	}

	if (kj->getAction_Next_Hor())
	{
		if (!active_nav_btns)
		{
			option_sliders[hoption]->increaseValue();
		}
		else
		{
			audio->playSound(0);
			changeOptionHor(moption - 1);
		}
	}

	//-------

	if (kj->getAction_Next())
	{
		audio->playSound(0);
		changeOptionVer(hoption + 1);
	}
	if (kj->getAction_Prev())
	{
		audio->playSound(0);
		changeOptionVer(hoption - 1);
	}
	// LOADING
	if (kj->getAction_Accept() && active_nav_btns)
	{
		audio->playSound(1);
		switch (moption)
		{
		case 0:
			active_first = false;
			changeOptionHor(2);
			break;
		case 1:
			loadScene(0);
			break;
		case 2:
			active_first = true;
			changeOptionHor(0);
			break;
		}
	}
}

void OptionsScene::draw()
{
	SDL_RenderCopy(ren, bg, NULL, NULL);

	btns_txt[1]->draw(); // buttton: "BACK"

	if (active_first)
	{
		for (UISlider* s : option_sliders)
		{
			s->draw();
		}

		btns_txt[0]->draw(); // right arrow btn
	}
	else 
	{
		Scene::draw();
		btns_txt[2]->draw(); // left arrow btn
	}
}

void OptionsScene::OnLoad()
{
	Scene::OnLoad();
}

void OptionsScene::OnUnload()
{
	Scene::OnUnload();
}

void OptionsScene::changeOptionHor(int _new)
{
	if (_new < (active_first ? 0 : 1))
		_new = btns_txt.size() - (active_first ? 2 : 1);
	else if (_new >= (active_first ? btns_txt.size() - 1 : btns_txt.size()))
		_new = (active_first ? 0 : 1);

	btns_txt[moption]->setNewFontAsset(font_def_btn);
	btns_txt[_new]->setNewFontAsset(font_hover_btn);

	moption = _new;
}

void OptionsScene::changeOptionVer(int _new)
{
	if (!active_first)
		return;

	int size = option_sliders.size() - 1;

	if (_new < 0)
	{
		_new = size;
		active_nav_btns = !active_nav_btns;
	}

	if (_new > size)
	{
		active_nav_btns = !active_nav_btns;
		_new = 0;
	}

	option_sliders[hoption]->unfocus();
	if(!active_nav_btns)
		option_sliders[_new]->focus();

	hoption = _new;
}
