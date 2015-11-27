#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Camera.h"
#include "Common.h"
#include "Transform.h"
#include "Mesh.h"
#include "Scene.h"
#include "Component.h"

class GameObject
{
public:
	std::string name;
	Transform transform;

	glm::mat4 GetMVPMatrix()
	{
		return MainCamera->GetProjectionMatrix() * MainCamera->GetViewMatrix() * transform.GetWorldMatrix();
	}

	GameObject()
	{
		transform = Transform();
	}
	GameObject(std::string n)
	{
		transform = Transform();
		name = n;
	}
	~GameObject()
	{

	}

	std::vector<std::shared_ptr<Component>> GetComponents()
	{
		return components;
	}
	template <typename T>
	std::shared_ptr<T> AddComponent()
	{
		std::shared_ptr<T> component = std::shared_ptr<T>(new T());
		components.push_back(component);
		return component;
	}
	template <typename T>
	std::shared_ptr<T> GetComponent()
	{
		for (std::shared_ptr<Component> i : components)
		{
			if (std::dynamic_pointer_cast<T>(i) != NULL && std::dynamic_pointer_cast<T>(i) != nullptr)
			{
				return std::dynamic_pointer_cast<T>(i);
			}
		}
		return nullptr;
	}

private:
	std::vector<std::shared_ptr<Component>> components;
};

#endif