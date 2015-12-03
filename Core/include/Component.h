#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "Common.h"

class GameObject;
class Component
{
public:
	std::shared_ptr<GameObject> gameObject;

	Component()
	{

	}
	~Component()
	{

	}

	virtual void Start(){}
	virtual void Update(){}
	virtual void PreRender(){}
	virtual void PostRender(){}
	virtual void Input(SDL_Event* e){}
};

#endif