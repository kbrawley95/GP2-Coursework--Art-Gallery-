#ifndef _MESH_H
#define _MESH_H

#include "Component.h"
#include "Common.h"
#include "Vertex.h"
#include <fbxsdk.h>

class Mesh : public Component
{
public:
	vector<Vertex> vertices;
	vector<int> indices;

	Mesh();
	Mesh(string filename);

	~Mesh();

private:

	FbxString GetAttributeTypeName(FbxNodeAttribute::EType type);
	bool loadFBXFromFile(const std::string& filename);
	void processNode(FbxNode* node);
	void processAttribute(FbxNodeAttribute* attribute);
	void processMesh(FbxMesh* mesh);
	void processMeshTextureCoords(FbxMesh* mesh, Vertex* verts, int numVerts);
};

#endif