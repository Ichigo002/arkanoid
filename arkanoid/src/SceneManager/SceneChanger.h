#ifndef SCENE_CHANGER_H
#define SCENE_CHANGER_H

static int __load_sc_ = -1; // scene to load in next frame [-1 == nothing to reload]

// Loads next scene
void loadScene(int index);

bool sceneReadyToLoad();

int getSceneToLoad();

#endif // !SCENE_CHANGER_H
