#ifndef _MESH_H
#define _MESH_H

#include "Vertex.h"
#include "Component.h"

class Mesh : public Component
{
public:
	vector<Vertex> vertices;
	vector<int> indices;

	Mesh(shared_ptr<GameObject> g);
	~Mesh();

	void LoadFBX(string filename);

private:

	FbxString GetAttributeTypeName(FbxNodeAttribute::EType type);
	bool loadFBXFromFile(const std::string& filename);
	void processNode(FbxNode* node);
	void processAttribute(FbxNodeAttribute* attribute);
	void processMesh(FbxMesh* mesh);
	void processMeshTextureCoords(FbxMesh* mesh, Vertex* verts, int numVerts);
};

#endif