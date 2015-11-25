#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Common.h"
#include "Component.h"
#include "Transform.h"

class GameObject
{
public:
	string name;
	shared_ptr<Transform> transform;

	mat4 GetModelMatrix()
	{
		mat4 translationMatrix = translate(mat4(1.0f), transform->position.ConvertToVec3());
		mat4 scaleMatrix = scale(mat4(1.0f), transform->scale.ConvertToVec3());

		mat4 rotationMatrix = rotate(mat4(1.0f), transform->rotation.x, vec3(1.0f, 0.0f, 0.0f))*
			rotate(mat4(1.0f), transform->rotation.y, vec3(0.0f, 1.0f, 0.0f))*
			rotate(mat4(1.0f), transform->rotation.z, vec3(0.0f, 0.0f, 1.0f));

		modelMatrix = translationMatrix*scaleMatrix*rotationMatrix;
		return modelMatrix;
	}

	vector<shared_ptr<Component>> GetComponents()
	{
		return components;
	}

	void AddComponent(shared_ptr<Component> component)
	{
		component->gameObject = shared_ptr<GameObject>(this);
		components.push_back(component);
	}

	//Gets a component type that is attached to the gameobject (T is the type of component e.g. Mesh)
	template <typename T>
	shared_ptr<T> GetComponent()
	{
		for (shared_ptr<Component> i : components)
		{
			if (dynamic_pointer_cast<T>(i) != NULL && dynamic_pointer_cast<T>(i) != nullptr)
			{
				return dynamic_pointer_cast<T>(i);
			}
		}
		return NULL;
	}

private:
	vector<shared_ptr<GameObject>> children;
	vector<shared_ptr<Component>> components;
	mat4 modelMatrix;
};

#endif