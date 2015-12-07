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
	//Setup Engine
	Core* engine = new Core(800, 600);
	engine->lockCursor = true;

	//Main Light
	MainLight = std::shared_ptr<DirectionalLight>(new DirectionalLight());

	//Main camera
	MainCamera = std::shared_ptr<Camera>(new Camera());
	MainCamera->transform.position = Vector3(0, 0, -50);
	MainCamera->transform.rotation = Vector3(0, 0, 0);

	//Setup skybox
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
	
	//armored car
	std::shared_ptr<GameObject> obj = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Mesh> m = obj->AddComponent<Mesh>();
	std::shared_ptr<Material> objMat = std::shared_ptr<Material>(new Material(SHADER_PATH + "textureVS.glsl", SHADER_PATH + "textureFS.glsl"));
	objMat->LoadTexture(TEXTURE_PATH + "armoredrecon_diff.png");
	m->LoadFBX(MODEL_PATH + "armoredrecon.fbx", objMat);
	GameObjects.push_back(obj);
	obj->transform.position = Vector3(0,0,-10);

	//pickup truck
	std::shared_ptr<GameObject> obj2 = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Mesh> m2 = obj2->AddComponent<Mesh>();
	std::shared_ptr<Material> mat = std::shared_ptr<Material>(new Material(SHADER_PATH + "textureVS.glsl", SHADER_PATH + "textureFS.glsl"));
	mat->LoadTexture(TEXTURE_PATH + "truck_color-blue.png");
	m2->LoadFBX(MODEL_PATH + "L200-FBX.fbx", mat);
	GameObjects.push_back(obj2);
	obj2->transform.position = Vector3(0, -3, 0);
	obj2->transform.rotation = Vector3(0, 0, 0);
	obj2->transform.scale = Vector3(0.01f, 0.01f, 0.01f);

	//Start Game
	engine->Start();
}