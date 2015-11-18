#ifndef _COMPONENT_H
#define _COMPONENT_H

class GameObject;

class Component
{
public:
	GameObject* gameObject;

	Component()
	{

	}
	~Component()
	{

	}

	virtual void Update()
	{

	}
	virtual void Render()
	{

	}
	virtual void Start()
	{

	}
};

#endif