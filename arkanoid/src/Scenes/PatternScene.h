#ifndef xh
#define xh

#include "../SceneManager/Scene.h"
#include "../TextAsset/TextAsset.h"

class x : public Scene
{
public:
	x(SDL_Renderer* r, SDL_Event* e);
	~x();

	virtual void update();
	virtual void events();
	virtual void draw();

	virtual void OnLoad();
	virtual void OnUnload();

protected:


};

#endif