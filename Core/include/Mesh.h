#ifndef _MESH_H
#define _MESH_H

#include "Common.h"
#include "Material.h"
#include "Vertex.h"
#include "Component.h"
#include "GameObject.h"

class Mesh : public Component
{
public:
	std::vector<Vertex> vertices;
	std::vector<int> indices;

	GLuint VBO;
	GLuint EBO;
	GLuint VAO;
	GLuint skyboxVAO;

	bool LoadFBX(std::string filename);
	void GenerateBuffers();
	void GenerateSkyBoxBuffers();

	Mesh();
	~Mesh();

	void SetMaterial(std::shared_ptr<Material> mat);
	std::shared_ptr<Material> GetMaterial()
	{
		return material;
	}
	
private:
	std::shared_ptr<Material> material = nullptr;

	FbxString GetAttributeTypeName(FbxNodeAttribute::EType type);
	void ProcessNode(FbxNode* node, std::shared_ptr<GameObject> child);
	void ProcessAttribute(FbxNodeAttribute* attribute, std::shared_ptr<GameObject> child);
	void ProcessMesh(FbxMesh* mesh, std::shared_ptr<GameObject> child);
	void ProcessMeshTextureCoords(FbxMesh* mesh, Vertex* verts, int numVerts);
	void ProcessMeshNormals(FbxMesh * mesh, Vertex * verts, int numVerts);
};

#endif