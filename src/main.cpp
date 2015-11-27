#include "Core.h"

//I know its shit brian. Just trust!
#define SDL_main main
std::shared_ptr<Camera> MainCamera;
std::shared_ptr<Light> MainLight;
std::vector<std::shared_ptr<GameObject>> GameObjects;
float deltaTime;

int main(int argc, char *argv[])
{
	Core* engine = new Core(800, 600);

	MainCamera = std::shared_ptr<Camera>(new Camera());
	MainCamera->transform.position = Vector3(0, 0, -50);

	std::shared_ptr<GameObject> obj = std::shared_ptr<GameObject>(new GameObject());
	std::shared_ptr<Mesh> m = obj->AddComponent<Mesh>();
	m->LoadFBX(MODEL_PATH + "utah-teapot.fbx");
	m->material = std::shared_ptr<Material>(new Material(SHADER_PATH + "textureVS.glsl", SHADER_PATH + "textureFS.glsl"));
	m->material->LoadTexture(TEXTURE_PATH + "texture.png");
	m->GenerateBuffers();
	GameObjects.push_back(obj);

	engine->Start();
}