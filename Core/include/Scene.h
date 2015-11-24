#ifndef _SCENE_H
#define _SCENE_H

#include "Common.h"
#include "GameObject.h"
#include "Camera.h"
#include "Light.h"

class Scene
{
public:
	string name;
	shared_ptr<GameObject> camera;
	shared_ptr<GameObject> light;
	vector<shared_ptr<GameObject>> gameObjects;

	Scene(shared_ptr<Camera> camera);
	~Scene();
};

#endif