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
	m2->material = std::shared_ptr<Material>(new Material(SHADER_PATH + "textureVS.glsl", SHADER_PATH + "textureFS.glsl"));
	m2->material->LoadTexture(TEXTURE_PATH + "armoredrecon_diff.png");
	m2->GenerateBuffers();
	GameObjects.push_back(obj2);

	std::shared_ptr<GameObject> skybox = std::shared_ptr<GameObject>(new GameObject);
	skybox->transform.position = Vector3(20, 0, 0);
	std::shared_ptr<Mesh> skyboxMesh = skybox->AddComponent<Mesh>();

	const std::string skyboxFront = ASSET_PATH + TEXTURE_PATH + "ashcanyon_ft.png";
	const std::string skyboxBack = ASSET_PATH + TEXTURE_PATH + "ashcanyon_bk.png";
	const std::string skyboxLeft = ASSET_PATH + TEXTURE_PATH + "ashcanyon_lf.png";
	const std::string skyboxRight = ASSET_PATH + TEXTURE_PATH + "ashcanyon_rt.png";
	const std::string skyboxTop= ASSET_PATH + TEXTURE_PATH + "ashcanyon_up.png";
	const std::string skyboxBottom = ASSET_PATH + TEXTURE_PATH + "ashcanyon_dn.png";

	skyboxMesh->material->SetCubeMapTextures(skyboxFront, skyboxBack, skyboxLeft, skyboxRight, skyboxTop, skyboxBottom);
	skyboxMesh->GenerateBuffers();
	GameObjects.push_back(skybox);

	engine->Start();
}