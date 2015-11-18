#ifndef _SCENE_H
#define _SCENE_H

#include "Common.h"
#include "GameObject.h"
#include "Camera.h"

class Scene
{
public:
	string name;
	GameObject* camera;
	vector<GameObject*> gameObjects;

	Scene(Camera* camera);
	~Scene();
};

#endif