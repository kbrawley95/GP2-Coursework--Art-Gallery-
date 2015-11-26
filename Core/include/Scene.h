#ifndef _SCENE_H
#define _SCENE_H

#include "Common.h"
#include "GameObject.h"

extern float deltaTime;
extern shared_ptr<GameObject> MainCamera;
extern shared_ptr<GameObject> MainLight;
extern vector<shared_ptr<GameObject>> GameObjects;

#endif