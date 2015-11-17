#ifndef _SCENE_H
#define _SCENE_H

#include "GameObject.h"

class Scene
{
public:
	Scene();
	~Scene();

	GameObject* FindGameObject(string name);
	void AddGameObject(GameObject* g);
	void RemoveGameObject(GameObject* g);

	

private:
	list<GameObject*> gameObjects;
	list<GameObject*>::iterator iter;
};

#endif

