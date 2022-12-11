#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <SDL.h>
#include <vector>
#include "../../SceneManager/Scene.h"
#include "../../Player/Player.h"

class Level
{
public:
	~Level();
	SDL_Texture* bg;
};

class GameScene : public Scene
{
public:
	GameScene(SDL_Renderer* r, AudioPlayer* ap, KeyJoy* k);

	virtual ~GameScene();

	virtual void update();
	virtual void events();
	virtual void draw();

	virtual void OnLoad();
	virtual void OnUnload();

protected:
	/// <summary>
	/// Loads level based on index
	/// </summary>
	void loadLvl(int lvl);
	void unloadLvl();

protected:
	Level* current_lvl; // currently loaded level
	SDL_Rect lvl_bg_dstR;
	int curr_index_lvl;
	Player* paddle;
};

#endif