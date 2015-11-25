#ifndef _COMPONENTS_H
#define _COMPONENTS_H

#include "Common.h"

class GameObject;

class Component
{
public:
	shared_ptr<GameObject> gameObject;

	Component(shared_ptr<GameObject> g)
	{
		gameObject = g;
	}

	~Component()
	{

	}

	virtual void Start()
	{

	}

	virtual void Input(SDL_Event* e)
	{

	}

	virtual void Update()
	{

	}

	virtual void Render()
	{

	}

};

#endif