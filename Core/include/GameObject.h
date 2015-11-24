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