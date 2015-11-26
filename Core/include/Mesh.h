#ifndef _MESH_H
#define _MESH_H

#include "Common.h"
#include "Vertex.h"
#include "Component.h"
#include "GameObject.h"
#include "Material.h"
#include "Scene.h"
#include "Camera.h"

class Mesh : public Component
{
public:
	shared_ptr<Material> material;
	vector<Vertex> vertices;
	vector<int> indices;

	Mesh(shared_ptr<GameObject> g);
	~Mesh();

	void Render();
	void GenerateBuffers();

	void SetMaterial(shared_ptr<Material> mat)
	{
		material = mat;
	}
	shared_ptr<Material> GetMaterial()
	{
		return material;
	}

private:
	GLuint VBO;
	GLuint EBO;
	GLuint VAO;
};

#endif