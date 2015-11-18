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
	

	void LoadShader(const string& vsFilename, const string& fsFilename, Shader* shader);

	GLuint GetVertexArrayObject()
	{
		return m_VAO;
	};

	GLuint GetShaderProgram()
	{
		return m_ShaderProgram;
	};

	vec4& GetAmbientMaterial()
	{
		return m_AmbientMaterial;
	};

	vec4& GetDiffuseMaterial()
	{
		return m_DiffuseMaterial;
	};

	vec4& GetSpecularMaterial()
	{
		return m_SpecularMaterial;
	};

	float GetSpecularPower()
	{
		return m_SpecularPower;
	};

	int GetNumberOfIndices()
	{
		return m_NoOfIndices;
	};

	int GetNumberOfVetices()
	{
		return m_NoOfVertices;
	};

	GLuint GetDiffuseMap()
	{
		return m_DiffuseMap;
	};


	GameObject();
	~GameObject();

private:

	mat4 m_ModelMatrix;

	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_VAO;
	GLuint m_ShaderProgram;
	int m_NoOfIndices;
	int m_NoOfVertices;

	vec3 m_Position;
	vec3 m_Rotation;
	vec3 m_Scale;

	vec4 m_AmbientMaterial;
	vec4 m_DiffuseMaterial;
	vec4 m_SpecularMaterial;
	float m_SpecularPower;

	GLuint m_DiffuseMap;
	
};

#endif