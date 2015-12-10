#include "Mesh.h"

bool Mesh::LoadFBX(std::string filename, std::shared_ptr<Material> mat)
{
	material = mat;
	std::cout << "Loading " << filename << std::endl;
	//Initialize the SDK manager. This object handles memory management
	FbxManager* sdkManager = FbxManager::Create();

	//Create the IO settings
	FbxIOSettings* ioSettings = FbxIOSettings::Create(sdkManager, IOSROOT);
	sdkManager->SetIOSettings(ioSettings);

	//Create an importer using the sdk manager
	FbxImporter* importer = FbxImporter::Create(sdkManager, "");

	//Call the initalise method which will load the contents of the fbx file
	if (!importer->Initialize(filename.c_str(), -1, sdkManager->GetIOSettings()))
	{
		std::cout << "Could not find file " << filename << std::endl;
		return false;
	}

	//Create a new scene so that it can be populated by the imported file.
	FbxScene* scene = FbxScene::Create(sdkManager, "myScene");
	//Import the contents of the file into the scene
	importer->Import(scene);

	FbxGeometryConverter geometryConverter(sdkManager);
	geometryConverter.Triangulate(scene, true);

	//Process Nodes
	FbxNode* rootNode = scene->GetRootNode();
	if (rootNode)
	{
		for (int i = 0; i < rootNode->GetChildCount(); i++)
			ProcessNode(rootNode->GetChild(i), gameObject);
	}

	importer->Destroy();

	return true;
}

void Mesh::GenerateBuffers()
{
	for (std::shared_ptr<GameObject> i : (*gameObject).GetChildren())
	{
		std::shared_ptr<Mesh> m = i->GetComponent<Mesh>();
		if (m != nullptr)
			m->GenerateBuffers();
	}
	
	if (vertices.size() == 0)
		return;
	if (material == nullptr)
	{
		std::cout << "No Material found. Using default material & texture" << std::endl;
		material = std::shared_ptr<Material>(new Material(SHADER_PATH + "textureVS.glsl", SHADER_PATH + "textureFS.glsl"));
		material->LoadTexture(TEXTURE_PATH + "default.png");
	}
	//Generate Vertex Array
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	//create buffer
	glGenBuffers(1, &EBO);
	//Make the EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//Copy Index data to the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(int), &indices[0], GL_STATIC_DRAW);

	
	//Tell the shader that 0 is the position element
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, colour));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
}

Mesh::Mesh()
{

}
Mesh::~Mesh()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	vertices.clear();
	indices.clear();
}

void Mesh::SetMaterial(std::shared_ptr<Material> mat)
{
	material = mat;
}


//PRIVATE

//Return a string based representation based on the attribute type
FbxString Mesh::GetAttributeTypeName(FbxNodeAttribute::EType type)
{
	switch (type)
	{
	case fbxsdk::FbxNodeAttribute::eUnknown:
		return "unidentified";
	case fbxsdk::FbxNodeAttribute::eNull:
		return "null";
	case fbxsdk::FbxNodeAttribute::eMarker:
		return "marker";
	case fbxsdk::FbxNodeAttribute::eSkeleton:
		return "skeleton";
	case fbxsdk::FbxNodeAttribute::eMesh:
		return "mesh";
	case fbxsdk::FbxNodeAttribute::eNurbs:
		return "nurbs";
	case fbxsdk::FbxNodeAttribute::ePatch:
		return "patch";
	case fbxsdk::FbxNodeAttribute::eCamera:
		return "camera";
	case fbxsdk::FbxNodeAttribute::eCameraStereo:
		return "stereo";
	case fbxsdk::FbxNodeAttribute::eCameraSwitcher:
		return "camera switcher";
	case fbxsdk::FbxNodeAttribute::eLight:
		return "light";
	case fbxsdk::FbxNodeAttribute::eOpticalReference:
		return "optical reference";
	case fbxsdk::FbxNodeAttribute::eOpticalMarker:
		return "optical marker";
	case fbxsdk::FbxNodeAttribute::eNurbsCurve:
		return "nurbs curve";
	case fbxsdk::FbxNodeAttribute::eTrimNurbsSurface:
		return "trim nurbs surface";
	case fbxsdk::FbxNodeAttribute::eBoundary:
		return "boundary";
	case fbxsdk::FbxNodeAttribute::eNurbsSurface:
		return "nurbs surface";
	case fbxsdk::FbxNodeAttribute::eShape:
		return "shape";
	case fbxsdk::FbxNodeAttribute::eLODGroup:
		return "LOD Group";
	case fbxsdk::FbxNodeAttribute::eSubDiv:
		return "subdivision";
	default:
		return "unknown";
	}
}

void Mesh::ProcessNode(FbxNode* node, std::shared_ptr<GameObject> parent)
{
	const char* nodeName = node->GetName();
	std::shared_ptr<GameObject> child = std::shared_ptr<GameObject>(new GameObject(nodeName));
	child->AddComponent<Mesh>()->material = material;
	parent->AddChild(child);
	FbxDouble3 translation = node->LclTranslation.Get();
	FbxDouble3 rotation = node->LclRotation.Get();
	FbxDouble3 scaling = node->LclScaling.Get();

	child->transform.position = Vector3(translation[0], translation[1], translation[2]);
	child->transform.rotation = Vector3(rotation[0], rotation[1], rotation[2]);
	child->transform.scale = Vector3(scaling[0], scaling[1], scaling[2]);

	//Print the node's attributes
	for (int i = 0; i < node->GetNodeAttributeCount(); i++)
		ProcessAttribute(node->GetNodeAttributeByIndex(i), child);

	//Recursively print the children
	for (int j = 0; j < node->GetChildCount(); j++)
		ProcessNode(node->GetChild(j), child);
}

void Mesh::ProcessAttribute(FbxNodeAttribute* attribute, std::shared_ptr<GameObject> child)
{
	if (!attribute)
		return;

	FbxString typeName = GetAttributeTypeName(attribute->GetAttributeType());
	FbxString attrName = attribute->GetName();
	switch (attribute->GetAttributeType())
	{
	case FbxNodeAttribute::eMesh:
		ProcessMesh(attribute->GetNode()->GetMesh(), child);
		break;
	case FbxNodeAttribute::eCamera:
	case FbxNodeAttribute::eLight:
	default:
		break;
	}
}

void Mesh::ProcessMesh(FbxMesh* mesh, std::shared_ptr<GameObject> child)
{
	int numVerts = mesh->GetControlPointsCount();
	int numIndices = mesh->GetPolygonVertexCount();

	Vertex* verts = new Vertex[numVerts];
	int* inds = mesh->GetPolygonVertices();

	for (int i = 0; i < numVerts; i++)
	{
		FbxVector4 currentVert = mesh->GetControlPointAt(i);
		verts[i].position = glm::vec3(currentVert[0], currentVert[1], currentVert[2]);
		verts[i].colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		verts[i].normal = glm::vec3(0.0f, 0.0f, 0.0f);
		verts[i].texCoords = glm::vec2(0.0f, 0.0f);
	}

	ProcessMeshTextureCoords(mesh, verts, numVerts);
	ProcessMeshNormals(mesh, verts, numVerts);

	for (int i = 0; i < numVerts; i++)
		child->GetComponent<Mesh>()->vertices.push_back(verts[i]);

	for (int i = 0; i < numIndices; i++)
		child->GetComponent<Mesh>()->indices.push_back(inds[i]);

	child->GetComponent<Mesh>()->GenerateBuffers();

	if (verts)
	{
		delete[] verts;
		verts = NULL;
	}
}

void Mesh::ProcessMeshTextureCoords(FbxMesh* mesh, Vertex* verts, int numVerts)
{
	for (int polygon = 0; polygon < mesh->GetPolygonCount(); polygon++)
	{
		for (unsigned polygonVertex = 0; polygonVertex < 3; polygonVertex++)
		{
			int fbxCornerIndex = mesh->GetPolygonVertex(polygon, polygonVertex);

			FbxVector2 fbxUV = FbxVector2(0.0, 0.0);
			FbxLayerElementUV* fbxLayerUV = mesh->GetLayer(0)->GetUVs();

			//Get texture coordinate
			if (fbxLayerUV)
			{
				int UVIndex = 0;
				switch (fbxLayerUV->GetMappingMode())
				{
				case FbxLayerElement::eByControlPoint:
					UVIndex = fbxCornerIndex;
					break;
				case FbxLayerElement::eByPolygonVertex:
					UVIndex = mesh->GetTextureUVIndex(polygon, polygonVertex, FbxLayerElement::eTextureDiffuse);
					break;
				case FbxLayerElement::eByPolygon:
					UVIndex = polygon;
					break;
				}

				fbxUV = fbxLayerUV->GetDirectArray().GetAt(UVIndex);
				verts[fbxCornerIndex].texCoords.x = fbxUV[0];
				verts[fbxCornerIndex].texCoords.y = 1.0f - fbxUV[1]; //y is inverted

			}
		}
	}
}

void Mesh::ProcessMeshNormals(FbxMesh * mesh, Vertex * verts, int numVerts)
{
	for (int iPolygon = 0; iPolygon < mesh->GetPolygonCount(); iPolygon++) {
		for (unsigned iPolygonVertex = 0; iPolygonVertex < 3; iPolygonVertex++) {
			int fbxCornerIndex = mesh->GetPolygonVertex(iPolygon, iPolygonVertex);
			FbxVector4 fbxNormal;
			mesh->GetPolygonVertexNormal(iPolygon, iPolygonVertex, fbxNormal);
			fbxNormal.Normalize();
			verts[fbxCornerIndex].normal.x = fbxNormal[0];
			verts[fbxCornerIndex].normal.y = fbxNormal[1];
			verts[fbxCornerIndex].normal.z = fbxNormal[2];
		}
	}
}