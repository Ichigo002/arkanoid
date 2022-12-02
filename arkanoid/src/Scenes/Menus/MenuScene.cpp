#include "MenuScene.h"

MenuScene::MenuScene(SDL_Renderer* r, SDL_Event* e)
	: Scene(r, e)
{
	SDL_Color col = { 255, 255, 0 };
	font = new FontAsset(ren, "assets/fonts/prstart.ttf", 25, col);

	txt = new TextAsset(font, "To jest testowy napis");

	kj = new KeyJoy(e);
}

MenuScene::~MenuScene()
{
}

void MenuScene::update()
{
}

void MenuScene::events()
{
	kj->events();

	txt->setText("Clicked: " + std::to_string(kj->getAction_Prev()));
}

void MenuScene::draw()
{
	txt->draw();
}

void MenuScene::OnLoad()
{
	txt->setStartingPos(30, 500);
	txt->setText("MenuScene test !!!");
}

void MenuScene::OnUnload()
{

}
