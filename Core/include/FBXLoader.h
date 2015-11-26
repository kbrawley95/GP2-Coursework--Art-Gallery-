#include "Common.h"
#include "Vertex.h"
#include "GameObject.h"
#include "Material.h"
#include "Mesh.h"


shared_ptr<GameObject> loadFBXFromFile(const string& filename);

void processNode(FbxNode *node, shared_ptr<GameObject> parent);
void processAttribute(FbxNodeAttribute * attribute, shared_ptr<GameObject> gameObject);
void processMesh(FbxMesh * mesh, shared_ptr<GameObject> gameObject);
void processMeshTextureCoords(FbxMesh * mesh, shared_ptr<Mesh> m);
void processMeshNormals(FbxMesh * mesh, shared_ptr<Mesh> m);