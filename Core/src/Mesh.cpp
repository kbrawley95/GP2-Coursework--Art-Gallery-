#include "Mesh.h"

Mesh::Mesh()
{

}

Mesh::Mesh(string filename)
{
	std::cout << "Loading " + filename << std::endl;
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
		cout << "ERROR: loading " + filename << endl;
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
			processNode(rootNode->GetChild(i));
	}

	importer->Destroy();
}

Mesh::~Mesh()
{
	vertices.clear();
	indices.clear();
}

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
	case fbxsdk::FbxNodeAttribute::eCachedEffect:
		return "cached effect";
	case fbxsdk::FbxNodeAttribute::eLine:
		return "line";
	default:
		return "unknown";
	}
}

void Mesh::processNode(FbxNode* node)
{
	const char* nodeName = node->GetName();
	FbxDouble3 translation = node->LclTranslation.Get();
	FbxDouble3 rotation = node->LclRotation.Get();
	FbxDouble3 scaling = node->LclScaling.Get();

	//Print the node's attributes
	for (int i = 0; i < node->GetNodeAttributeCount(); i++)
		processAttribute(node->GetNodeAttributeByIndex(i));

	//Recursively print the children
	for (int j = 0; j < node->GetChildCount(); j++)
		processNode(node->GetChild(j));
}

void Mesh::processAttribute(FbxNodeAttribute* attribute)
{
	if (!attribute)
		return;

	FbxString typeName = GetAttributeTypeName(attribute->GetAttributeType());
	FbxString attrName = attribute->GetName();
	switch (attribute->GetAttributeType())
	{
	case FbxNodeAttribute::eMesh:
		processMesh(attribute->GetNode()->GetMesh());
		break;
	case FbxNodeAttribute::eCamera:
	case FbxNodeAttribute::eLight:
	default:
		break;
	}
}

void Mesh::processMesh(FbxMesh* mesh)
{
	int numVerts = mesh->GetControlPointsCount();
	int numIndices = mesh->GetPolygonVertexCount();
	verticesSize = numVerts;
	indicesSize = numIndices;

	Vertex* verts = new Vertex[numVerts];
	int* ind = mesh->GetPolygonVertices();

	for (int i = 0; i < numVerts; i++)
	{
		FbxVector4 currentVert = mesh->GetControlPointAt(i);
		verts[i].position = vec3(currentVert[0], currentVert[1], currentVert[2]);
		verts[i].colour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		verts[i].texCoords = vec2(0.0f, 0.0f);
	}

	processMeshTextureCoords(mesh, verts, numVerts);

	for (int i = 0; i < numVerts; i++)
		vertices.push_back(verts[i]);

	for (int i = 0; i < numIndices; i++)
		indices.push_back(ind[i]);

	if (verts)
	{
		delete[] verts;
		verts = NULL;
	}
}

void Mesh::processMeshTextureCoords(FbxMesh* mesh, Vertex* verts, int numVerts)
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