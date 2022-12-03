#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include "../AudioPlayer/AudioPlayer.h"
#include "../KeyJoy/KeyJoy.h"
#include <vector>
#include <SDL.h>

class SceneManager
{
public:
	SceneManager(SDL_Renderer* r, SDL_Event* e);
	~SceneManager();

	/// <summary>
	/// Adds new Scene to query
	/// </summary>
	/// <typeparam name="T">Type class with Level Scene</typeparam>
	/// <returns>id of scene</returns>
	template <class T>
	int addScene();

	/// <summary>
	/// Removes Scene by id
	/// </summary>
	/// <param name="id"></param>
	/// <returns>0 on succes or negative on fail</returns>
	int rmvScene(int id);

	/// <summary>
	/// Load scene with id and automatically unload last loaded scene
	/// </summary>
	/// <returns>0 on succes or negative on fail</returns>
	int loadScene(int id);

	int unloadScene();

	void events();
	void update();
	void draw();
private:
	bool validateId(int id);

private:
	SDL_Renderer* ren;
	SDL_Event* eve;
	AudioPlayer* audio;
	KeyJoy* kj;

	std::vector<Scene*> scenes;
	Scene* loadedScene;
};

template<class T>
inline int SceneManager::addScene()
{
	T* s = new T(ren, audio, kj);
	scenes.push_back(s);
	return scenes.size() - 1;
}

#endif