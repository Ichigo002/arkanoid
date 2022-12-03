#include "MenuScene.h"

MenuScene::MenuScene(SDL_Renderer* r, SDL_Event* e)
	: Scene(r, e)
{
	SDL_Color col = { 255, 255, 0 };
	font = new FontAsset(ren, "assets/fonts/prstart.ttf", 25, col);

	txt = new TextAsset(font, "To jest testowy napis");

	kj = new KeyJoy(e);

	audio = new AudioPlayer();
	audio->addMusic("assets/Music/ES_A Walk in Marais - The Fly Guy Five.mp3");
	audio->addSoundEffect("assets/Effects/FunkyVoices_Female_Jane_Discovery_Aha_01.wav");
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

	//txt->setText("Clicked: " + std::to_string(kj->getAction_Prev()));

	if (kj->getAction_Prev())
	{
		audio->playSound(0);
	}
	if (kj->getAction_Pause())
	{
		if (audio->isPausedMusic())
			audio->resumeMusic();
		else
			audio->pauseMusic();
	}
	if(kj->getAction_Accept())
		audio->playMusic(0);
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
