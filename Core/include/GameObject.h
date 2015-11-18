#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Common.h"
#include "Transform.h"
#include "Component.h"

class GameObject
{
public:
	string name;
	string tag;
	Transform transform;
	vector<GameObject*> children;
	vector<Component*> components;

	//Gets a component type that is attached to the gameobject (T is the type of component e.g. Mesh)
	template <typename T>
	T* GetComponent()
	{
		for (Component* m : components)
		{
			if (dynamic_cast<T*>(m) != NULL)
			{
				return dynamic_cast<T*>(m);
			}
		}
		return NULL;
	}

	GameObject();
	~GameObject();
};

#endif