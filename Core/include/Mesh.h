#ifndef _MESH_H
#define _MESH_H

#include "Common.h"
#include "Material.h"
#include "Vertex.h"
#include "Component.h"

class Mesh : public Component
{
public:
	std::vector<Vertex> vertices;
	std::vector<int> indices;
	std::shared_ptr<Material> material = nullptr;

	GLuint VBO;
	GLuint EBO;
	GLuint VAO;

	bool LoadFBX(std::string filename);
	void GenerateBuffers();

	Mesh();
	~Mesh();
	
private:

	FbxString GetAttributeTypeName(FbxNodeAttribute::EType type);
	void ProcessNode(FbxNode* node);
	void ProcessAttribute(FbxNodeAttribute* attribute);
	void ProcessMesh(FbxMesh* mesh);
	void ProcessMeshTextureCoords(FbxMesh* mesh, Vertex* verts, int numVerts);
};

#endif