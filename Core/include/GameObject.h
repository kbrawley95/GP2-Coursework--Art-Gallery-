#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Common.h"
#include "Component.h"
#include "Transform.h"
#include "Scene.h"
#include "Texture.h"

class GameObject : public enable_shared_from_this<GameObject>
{
public:
	string name;
	Transform transform;

	GameObject()
	{
		parent = nullptr;
	}
	GameObject(string name)
	{
		GameObject::name = name;
	}	

	mat4 GetModelMatrix()
	{
		mat4 translationMatrix = translate(mat4(1.0f), transform.position.ConvertToVec3());
		mat4 scaleMatrix = scale(mat4(1.0f), transform.scale.ConvertToVec3());

		mat4 rotationMatrix = rotate(mat4(1.0f), transform.rotation.x, vec3(1.0f, 0.0f, 0.0f))*
			rotate(mat4(1.0f), transform.rotation.y, vec3(0.0f, 1.0f, 0.0f))*
			rotate(mat4(1.0f), transform.rotation.z, vec3(0.0f, 0.0f, 1.0f));

		mat4 modelMatrix = scaleMatrix * rotationMatrix * translationMatrix;
		if (parent != nullptr)
			modelMatrix *= parent->GetModelMatrix();
		return modelMatrix;
	}
	
	void Start()
	{
		for (auto i = components.begin(); i != components.end(); ++i)
			(*i)->Start();

		for (auto i = children.begin(); i != children.end(); ++i)
			(*i)->Start();
	}
	void Update()
	{
		for (auto i = components.begin(); i != components.end(); ++i)
			(*i)->Update();

		for (auto i = children.begin(); i != children.end(); ++i)
			(*i)->Update();
	}
	void Render()
	{
		for (auto i = components.begin(); i != components.end(); ++i)
			(*i)->Render();

		for (auto i = children.begin(); i != children.end(); ++i)
			(*i)->Render();
	}
	void Input(SDL_Event* e)
	{
		for (auto i = components.begin(); i != components.end(); ++i)
			(*i)->Input(e);

		for (auto i = children.begin(); i != children.end(); ++i)
			(*i)->Input(e);
	}

	void AddChild(shared_ptr<GameObject> g)
	{
		g->parent = shared_from_this();
		children.push_back(g);
	}
	vector<shared_ptr<GameObject>>* GetChildern()
	{
		return &children;
	}

	const vector<shared_ptr<Component>>& GetComponents()
	{
		return components;
	}
	template <typename T>
	shared_ptr<T> AddComponent()
	{
		shared_ptr<T> component = shared_ptr<T>(new T(shared_from_this()));
		components.push_back(component);
		return component;
	}
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
		return nullptr;
	}

private:
	shared_ptr<GameObject> parent;
	vector<shared_ptr<GameObject>> children;
	vector<shared_ptr<Component>> components;
};

#endif