#include "SceneChanger.h"

void loadScene(int index)
{
	__load_sc_ = index;
}

bool sceneReadyToLoad()
{
	return __load_sc_ != -1;
}

int getSceneToLoad()
{
	int _v = __load_sc_;
	__load_sc_ = -1;
	return _v;
}
