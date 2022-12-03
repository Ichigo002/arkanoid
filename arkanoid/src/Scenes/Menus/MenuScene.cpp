#include "MenuScene.h"

MenuScene::MenuScene(SDL_Renderer* r, SDL_Event* e)
	: Scene(r, e)
{
	SDL_Color col = { 255, 255, 0 };
	font = new FontAsset(ren, "assets/fonts/prstart.ttf", 25, col);

	txt = new TextAsset(font, "To jest testowy napis");

	kj = new KeyJoy(e);

	Mix_Init(MIX_INIT_MP3);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "Error: " << Mix_GetError() << "\n";

	Mix_VolumeMusic(64);

	music = Mix_LoadMUS("assets/Music/ES_A Walk in Marais - The Fly Guy Five.mp3");
	sound = Mix_LoadWAV("assets/Effects/FunkyVoices_Female_Jane_Discovery_Aha_01.wav");
}

MenuScene::~MenuScene()
{
	Mix_Quit();
	Mix_FreeChunk(sound);
	Mix_FreeMusic(music);
}

void MenuScene::update()
{
}

void MenuScene::events()
{
	kj->events();

	txt->setText("Clicked: " + std::to_string(kj->getAction_Prev()));

	if (kj->getPressedKey(SDLK_5))
	{
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(music, -1);
		}
		else if (Mix_PausedMusic())
		{
			Mix_ResumeMusic();
		}
		else
		{
			Mix_PauseMusic();
		}
	}

	if (kj->getPressedKey(SDLK_6))
	{
		Mix_HaltMusic();
	}

	if (kj->getPressedKey(SDLK_7))
	{
		Mix_PlayChannel(-1, sound, 0);
	}
	if (kj->getPressedKey(SDLK_8))
	{
		Mix_PlayChannel(-1, sound, 0);
	}
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
