#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Camera.h"
#include "Common.h"
#include "Transform.h"
#include "Mesh.h"
#include "Scene.h"
#include "Component.h"

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
	std::string name;
	Transform transform;
	std::shared_ptr<GameObject> parent;

	glm::mat4x4 GetMVPMatrix()
	{
		glm::mat4x4 MVP = MainCamera->GetProjectionMatrix() * MainCamera->GetViewMatrix();

		MVP = MVP * MultiplyParentMatrix(shared_from_this(), transform.GetWorldMatrix());

		return MVP;
	}

	GameObject()
	{
		transform = Transform();
		parent = nullptr;
	}
	GameObject(std::string n)
	{
		transform = Transform();
		name = n;
		parent = nullptr;
	}
	~GameObject()
	{

	}

	std::vector<std::shared_ptr<GameObject>> GetChildren()
	{
		return children;
	}
	std::shared_ptr<GameObject> GetChild(int x)
	{
		return children[x];
	}
	void AddChild(std::shared_ptr<GameObject> child)
	{
		child->parent = shared_from_this();
		children.push_back(child);
	}

	std::vector<std::shared_ptr<Component>> GetComponents()
	{
		return components;
	}
	template <typename T>
	std::shared_ptr<T> AddComponent()
	{
		std::shared_ptr<Component> component = std::shared_ptr<T>(new T());
		component->gameObject = shared_from_this();
		components.push_back(component);
		return std::dynamic_pointer_cast<T>(component);
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
	std::vector<std::shared_ptr<GameObject>> children;

	glm::mat4x4 MultiplyParentMatrix(std::shared_ptr<GameObject> child, glm::mat4x4 modelMatrix)
	{
		if (child->parent == nullptr)
			return modelMatrix;
		else
		{
			modelMatrix = child->parent->transform.GetWorldMatrix() * modelMatrix;
			return MultiplyParentMatrix(child->parent, modelMatrix);
		}
	}
};

#endif