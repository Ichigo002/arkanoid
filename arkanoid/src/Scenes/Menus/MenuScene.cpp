#include "MenuScene.h"

MenuScene::MenuScene(SDL_Renderer* r, AudioPlayer* ap, KeyJoy* k)
	: Scene(r, ap, k)
{
	SDL_Color c = { 255, 255, 255 };
	font_def = new FontAsset(r, "assets/Fonts/Pixelmania.ttf", 30, c);
	c = { 100, 130, 0 };
	font_hover = new FontAsset(r, "assets/Fonts/Pixelmania.ttf", 30, c);

	txts.push_back(new TextAsset(font_def, "PLAY"));
	txts[txts.size() - 1]->setStartingPos(250, 500);

	txts.push_back(new TextAsset(font_def, "OPTIONS"));
	txts[txts.size() - 1]->setStartingPos(183, 572);

	txts.push_back(new TextAsset(font_def, "EXIT"));
	txts[txts.size() - 1]->setStartingPos(252, 644);

	bg = TextureManager::load(r, "assets/Texture/bg_menu.png");
}

MenuScene::~MenuScene()
{
}

void MenuScene::update()
{
	Scene::update();
	//txts[2]->setStartingPos(mpos);
}

void MenuScene::events()
{
	if (kj->getAction_Accept())
	{
		std::cout << "Item pos: " << mpos << std::endl;
	}

	if (kj->getEventData()->type == SDL_MOUSEMOTION)
	{
		mpos.x = kj->getEventData()->button.x;
		mpos.y = kj->getEventData()->button.y;
	}

	Scene::events();
}

void MenuScene::draw()
{
	SDL_RenderCopy(ren, bg, NULL, NULL);
	Scene::draw();
}

void MenuScene::OnLoad()
{
	Scene::OnLoad();
}

void MenuScene::OnUnload()
{
	Scene::OnUnload();
}
