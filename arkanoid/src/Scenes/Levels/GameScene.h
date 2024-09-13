#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <SDL.h>
#include <vector>
#include <cstdlib>
#include "../../TextAsset/TextAsset.h"
#include "../../SceneManager/Scene.h"
#include "../../Player/Player.h"
#include "../../Ball/Ball.h"
#include "../../Brick/Brick.h"

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

	/// <summary>
	/// type of block between: 0-6
	/// or -1 if none
	/// </summary>
	/// <param name="arr"></param>
	void loadBricksByArr6x6(int arr[6][6]);

	void updateBricks();
	void updatePaddle();
	void updateMapBorders();
	void updateLogic();
	void updateCounters();

protected:
	Level* current_lvl; // currently loaded level
	SDL_Rect lvl_bg_dstR;

	int curr_index_lvl;
	int audio_hit_index;
	int audio_hit_brick_index;
	Player* paddle;
	Ball* ball;
	std::vector<Brick*> bricks;

	FontAsset* font_lose_text;
	TextAsset* lose_live_text; // lose text
	bool lose_life;
	Uint64 start_tick_lose;
	int pause_time_for_lose = 2000; //[ms]
	

	int hit_points;
	int combo_counter;

	int lives;
	int points;
	Vector2Int mpos;
};

#endif