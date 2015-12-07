#include "Core.h"
#include "Cube.h"

//I know its shit brian. Just trust!
#define SDL_main main
std::shared_ptr<Camera> MainCamera;
std::shared_ptr<DirectionalLight> MainLight;
std::shared_ptr<GameObject> SkyBox;
std::vector<std::shared_ptr<GameObject>> GameObjects;
float deltaTime;
Vector2 mousePosition;
std::map<int, bool> keysPressed;
Vector2 mouseDelta;

int main(int argc, char *argv[])
{
	Core* engine = new Core(800, 600);
	engine->lockCursor = true;

	MainLight = std::shared_ptr<DirectionalLight>(new DirectionalLight());

	MainCamera = std::shared_ptr<Camera>(new Camera());
	MainCamera->transform.position = Vector3(0, 0, -50);
	MainCamera->transform.rotation = Vector3(0, 0, 0);

	SkyBox = std::shared_ptr<GameObject>(new GameObject());
	SkyBox->transform.position = Vector3(0, 0, -40);
	std::shared_ptr<Mesh> skyboxMesh = SkyBox->AddComponent<Mesh>();
	skyboxMesh->vertices.clear();
	skyboxMesh->indices.clear();
	for (int i = 0; i < numberOfCubeVerts; i++)
		skyboxMesh->vertices.push_back(cubeVerts[i]);
	for (int i = 0; i < numberOfCubeIndices; i++)
		skyboxMesh->indices.push_back(cubeIndices[i]);

	
	const std::string skyboxTop = TEXTURE_PATH + "city_top.png";
	const std::string skyboxBottom = TEXTURE_PATH + "city_top.png";
	const std::string skyboxLeft = TEXTURE_PATH + "city_right.png";
	const std::string skyboxRight = TEXTURE_PATH + "city_left.png";
	const std::string skyboxFront = TEXTURE_PATH + "city_front.png";
	const std::string skyboxBack = TEXTURE_PATH + "city_back.png";

	skyboxMesh->SetMaterial(std::shared_ptr<Material>(new Material(SHADER_PATH + "skyVS.glsl", SHADER_PATH + "skyFS.glsl")));
	skyboxMesh->GetMaterial()->SetCubeMapTextures(skyboxLeft, skyboxRight, skyboxTop, skyboxBottom, skyboxFront, skyboxBack);
	skyboxMesh->GenerateBuffers();

	
	//Teapot
	std::shared_ptr<GameObject> obj = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Mesh> m = obj->AddComponent<Mesh>();
	std::shared_ptr<Material> objMat = std::shared_ptr<Material>(new Material(SHADER_PATH + "textureVS.glsl", SHADER_PATH + "textureFS.glsl"));
	objMat->LoadTexture(TEXTURE_PATH + "armoredrecon_diff.png");
	m->LoadFBX(MODEL_PATH + "armoredrecon.fbx", objMat);
	GameObjects.push_back(obj);
	obj->transform.position = Vector3(0,0,-10);

	//Armored Car
	std::shared_ptr<GameObject> obj2 = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Mesh> m2 = obj2->AddComponent<Mesh>();
	std::shared_ptr<Material> mat = std::shared_ptr<Material>(new Material(SHADER_PATH + "specularReflectionVS.glsl", SHADER_PATH + "specularReflectionFS.glsl"));
	mat->LoadTexture(TEXTURE_PATH + "armoredrecon_diff.png");
	m2->LoadFBX(MODEL_PATH + "art_gallery.fbx", mat);
	GameObjects.push_back(obj2);
	obj2->transform.position = Vector3(0, 0, 0);
	obj2->transform.rotation = Vector3(0, 180, 0);

/*
	std::shared_ptr<GameObject> pickup = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Mesh> pickMesh = pickup->AddComponent<Mesh>();
	std::shared_ptr<Material>pickMat = std::shared_ptr<Material>(new Material(SHADER_PATH + "textureVS.glsl", SHADER_PATH + "textureFS.glsl"));
	pickMat->LoadTexture(TEXTURE_PATH + "texture.png");
	pickMesh->LoadFBX(MODEL_PATH + "Gallery.fbx", pickMat);
	pickMesh->GenerateBuffers();
	GameObjects.push_back(pickup);
	obj2->transform.position = Vector3(0, 0, -40);
	obj2->transform.rotation = Vector3(0, 0, 0);*/

	//std::shared_ptr<GameObject> artGalleryObj = std::shared_ptr<GameObject>(new GameObject());
	//artGalleryObj->transform.position = Vector3(15, 0, 0);
	//std::shared_ptr<Mesh> modelMesh = artGalleryObj->AddComponent<Mesh>();
	//modelMesh->LoadFBX(MODEL_PATH + "Art_Gallery1.fbx");
	//modelMesh->material = std::shared_ptr<Material>(new Material(SHADER_PATH + "textureVS.glsl", SHADER_PATH + "textureFS.glsl"));
	//modelMesh->material->LoadTexture(TEXTURE_PATH + "texture.png");
	//modelMesh->GenerateBuffers();
	//GameObjects.push_back(artGalleryObj);

	engine->Start();
}