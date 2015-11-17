#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "Common.h"
#include "Vertices.h"

class GameObject
{
public:

	string name;

	GameObject();
	~GameObject();

	void update();

	void AddChild(shared_ptr<GameObject> child);

	void CreateBuffers(Vertex * pVerts, int numVerts, int *pIndices, int numIndices);
	void LoadShader(const string& vsFilename, const string& fsFilename);
	void LoadDiffuseMap(const string& filename);

	void SetPosition(const vec3& position)
	{
		m_Position = position;
	};

	void SetRotation(const vec3& rotation)
	{
		m_Rotation = rotation;
	};

	void SetScale(const vec3& scale)
	{
		m_Scale = scale;
	};

	int GetNumberOfChildren()
	{
		return m_ChildGameObjects.size();
	};

	GameObject * GetParent()
	{
		return m_ParentGameObject;
	};

	shared_ptr<GameObject> GetChild(int i)
	{
		return m_ChildGameObjects.at(i);
	};

	GLuint GetVertexArrayObject()
	{
		return m_VAO;
	};

	GLuint GetShaderProgram()
	{
		return m_ShaderProgram;
	};

	mat4& GetModelMatrix()
	{
		return m_ModelMatrix;
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
private:
	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_VAO;
	GLuint m_ShaderProgram;
	int m_NoOfIndices;
	int m_NoOfVertices;

	mat4 m_ModelMatrix;
	vec3 m_Position;
	vec3 m_Rotation;
	vec3 m_Scale;

	vec4 m_AmbientMaterial;
	vec4 m_DiffuseMaterial;
	vec4 m_SpecularMaterial;
	float m_SpecularPower;

	GLuint m_DiffuseMap;

	vector<shared_ptr<GameObject> > m_ChildGameObjects;
	GameObject * m_ParentGameObject;

};

#endif
