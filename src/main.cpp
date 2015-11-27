#include "Core.h"

//I know its shit brian. Just trust!
#define SDL_main main
std::shared_ptr<Camera> MainCamera;
std::shared_ptr<DirectionalLight> MainLight;
std::vector<std::shared_ptr<GameObject>> GameObjects;
float deltaTime;

int main(int argc, char *argv[])
{
	Core* engine = new Core(800, 600);

	MainLight = std::shared_ptr<DirectionalLight>(new DirectionalLight());

	MainCamera = std::shared_ptr<Camera>(new Camera());
	MainCamera->transform.position = Vector3(0, 0, -50);
	
	std::shared_ptr<GameObject> obj = std::shared_ptr<GameObject>(new GameObject());
	obj->transform.position = Vector3(15, 0, 0);
	std::shared_ptr<Mesh> m = obj->AddComponent<Mesh>();
	m->LoadFBX(MODEL_PATH + "utah-teapot.fbx");
	m->material = std::shared_ptr<Material>(new Material(SHADER_PATH + "textureVS.glsl", SHADER_PATH + "textureFS.glsl"));
	m->material->LoadTexture(TEXTURE_PATH + "texture.png");
	m->GenerateBuffers();
	GameObjects.push_back(obj);
	

	std::shared_ptr<GameObject> obj2 = std::shared_ptr<GameObject>(new GameObject());
	obj2->transform.position = Vector3(0, 0, -40);
	std::shared_ptr<Mesh> m2 = obj2->AddComponent<Mesh>();
	m2->LoadFBX(MODEL_PATH + "armoredrecon.fbx");
	m2->material = std::shared_ptr<Material>(new Material(SHADER_PATH + "testColourVS.glsl", SHADER_PATH + "testColourFS.glsl"));
	m2->material->LoadTexture(TEXTURE_PATH + "armoredrecon_diff.png");
	m2->GenerateBuffers();
	GameObjects.push_back(obj2);

	engine->Start();
}