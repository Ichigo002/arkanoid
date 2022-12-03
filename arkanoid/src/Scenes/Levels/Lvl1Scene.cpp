#include "Lvl1Scene.h"

Lvl1Scene::Lvl1Scene(SDL_Renderer* r, AudioPlayer* ap, KeyJoy* k)
	: LevelSceneManager(r, ap, k)
{
}

Lvl1Scene::~Lvl1Scene()
{
}

void Lvl1Scene::update()
{
	
}

void Lvl1Scene::events()
{
	LevelSceneManager::events();
}

void Lvl1Scene::draw()
{
}

void Lvl1Scene::OnLoad()
{
}

void Lvl1Scene::OnUnload()
{
}
