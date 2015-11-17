#ifndef _SCENE_H
#define _SCENE_H

#include "GameObject.h"

class Scene
{
public:
	Scene();
	~Scene();

	list<GameObject*> gameObjects;
	list<GameObject*>::iterator iter;

private:


};

#endif

