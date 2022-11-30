#include "SceneManager.h"

SceneManager::SceneManager(SDL_Renderer* r, SDL_Event* e)
	: ren(r), eve(e)
{
	loadedScene = nullptr;
}

SceneManager::~SceneManager()
{
	loadedScene = nullptr;
}

int SceneManager::rmvScene(int id)
{
	if (!validateId(id))
		return -1;
	scenes.erase(scenes.begin() + id);
	return 0;
}

int SceneManager::loadScene(int id)
{
	if (!validateId(id))
		return -1;
	unloadScene();

	loadedScene = scenes[id];
	loadedScene->OnLoad();

	return 0;
}

int SceneManager::unloadScene()
{
	if (loadedScene)
		loadedScene->OnUnload();
	else
		return -1;
	loadedScene = nullptr;
	return 0;
}

void SceneManager::events()
{
	if(loadedScene)
		loadedScene->events();
}

void SceneManager::update()
{
	if (loadedScene)
		loadedScene->update();
}

void SceneManager::draw()
{
	if (loadedScene)
		loadedScene->draw();
}

bool SceneManager::validateId(int id)
{
	return id >= 0 && id < scenes.size();
}
