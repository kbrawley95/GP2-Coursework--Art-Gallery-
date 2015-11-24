#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Common.h"
#include "Transform.h"
#include "Component.h"
#include "Shader.h"

class GameObject
{
public:
	string name;
	string tag;
	Transform transform;
	vector<shared_ptr<GameObject>> children;
	vector<shared_ptr<Component>> components;

	void AddComponent(shared_ptr<Component> component)
	{
		component->gameObject = this;
		components.push_back(component);
	}

	//Gets a component type that is attached to the gameobject (T is the type of component e.g. Mesh)
	template <typename T>
	shared_ptr<T> GetComponent()
	{
		for (auto m = components.begin(); m != components.end(); ++m)
		{
			cout << "working?" << endl;
		}
		return NULL;
	}

	mat4 GetModelMatrix();
	

	void LoadShader(const string& vsFilename, const string& fsFilename);


	int GetNumberOfIndices()
	{
		return m_NoOfIndices;
	};

	int GetNumberOfVetices()
	{
		return m_NoOfVertices;
	};


	GameObject();
	~GameObject();

private:

	mat4 m_ModelMatrix;


	int m_NoOfIndices;
	int m_NoOfVertices;

	vec3 m_Position;
	vec3 m_Rotation;
	vec3 m_Scale;

};

#endif