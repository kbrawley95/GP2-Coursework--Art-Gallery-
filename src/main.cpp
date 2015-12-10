#include "Core.h"

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
	//Setup engine
	Core* engine = new Core(800, 600);
	engine->lockCursor = true;

	//Main light
	MainLight = std::shared_ptr<DirectionalLight>(new DirectionalLight());

	//Main camera
	MainCamera = std::shared_ptr<Camera>(new Camera());
	MainCamera->transform.position = Vector3(0, 3, 100);
	MainCamera->transform.rotation = Vector3(0, 0, 0);

	//Setup skybox
	engine->SetSkyBox(TEXTURE_PATH + "winterplanetft.png", TEXTURE_PATH + "winterplanetbk.png", TEXTURE_PATH + "winterplanetlf.png", TEXTURE_PATH + "winterplanetrt.png", TEXTURE_PATH + "winterplanetup.png", TEXTURE_PATH + "winterplanetdn.png");
	
	//Armored car
	std::shared_ptr<GameObject> obj = engine->Instantiate();
	std::shared_ptr<Mesh> m = obj->AddComponent<Mesh>();
	std::shared_ptr<Material> objMat = std::shared_ptr<Material>(new Material(SHADER_PATH + "textureVS.glsl", SHADER_PATH + "textureFS.glsl"));
	objMat->LoadTexture(TEXTURE_PATH + "armoredrecon_diff.png");
	m->LoadFBX(MODEL_PATH + "armoredrecon.fbx", objMat);
	obj->transform.position = Vector3(0,0,30);

	//Pickup truck
	std::shared_ptr<GameObject> obj2 = engine->Instantiate();
	std::shared_ptr<Mesh> m2 = obj2->AddComponent<Mesh>();
	std::shared_ptr<Material> mat = std::shared_ptr<Material>(new Material(SHADER_PATH + "textureVS.glsl", SHADER_PATH + "textureFS.glsl"));
	mat->LoadTexture(TEXTURE_PATH + "truck_color-blue.png");
	m2->LoadFBX(MODEL_PATH + "L200-FBX.fbx", mat);
	obj2->transform.position = Vector3(0, -3, 60);
	obj2->transform.rotation = Vector3(0, 0, 0);
	obj2->transform.scale = Vector3(0.01f, 0.01f, 0.01f);

	//Enviorment
	std::shared_ptr<GameObject> environmentObj = engine->Instantiate();
	std::shared_ptr<Mesh> enviroMesh = environmentObj->AddComponent<Mesh>();
	std::shared_ptr<Material> enviroMat = std::shared_ptr<Material>(new Material(SHADER_PATH + "textureVS.glsl", SHADER_PATH + "textureFS.glsl"));
	enviroMat->LoadTexture(TEXTURE_PATH + "Building_V01_C.png");
	enviroMesh->LoadFBX(MODEL_PATH + "Street environment_V01.fbx", enviroMat);
	environmentObj->transform.position = Vector3(0, -50, 0);
	environmentObj->transform.rotation = Vector3(270,0 , 0);

	//Start game
	engine->Start();
}