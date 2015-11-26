#include "Core.h"

//I know its shit brian. Just trust!
#define SDL_main main
shared_ptr<GameObject> MainCamera;
shared_ptr<GameObject> MainLight;
vector<shared_ptr<GameObject>> GameObjects;
float deltaTime;

int main(int argc, char *argv[])
{
	Core* engine = new Core(800, 600);

	//Create Camera
	MainCamera = shared_ptr<GameObject>(new GameObject("Main Camera"));
	MainCamera->transform.position = Vector3(0, 0, 0);
	shared_ptr<Camera> cam = MainCamera->AddComponent<Camera>();
	cam->fov = 90;
	cam->aspect = 1;
	cam->zNear = 0.1f;
	cam->zFar = 100;
	GameObjects.push_back(MainCamera);

	//Create Light
	MainLight = shared_ptr<GameObject>(new GameObject());
	MainLight->AddComponent<Light>();
	GameObjects.push_back(MainLight);

	//Load Mesh Into Game Object
	shared_ptr<GameObject> obj = loadFBXFromFile(MODEL_PATH + "/armoredrecon.fbx");
	shared_ptr<Material> material = shared_ptr<Material>(new Material(shared_ptr<Shader>(new Shader(SHADER_PATH + "/textureVS.glsl", SHADER_PATH + "/textureFS.glsl"))));
	for (auto i = (*obj).GetChildern()->begin(); i != (*obj).GetChildern()->end(); ++i)
	{
		shared_ptr<Mesh> m = (*i)->GetComponent<Mesh>();
		if (m != nullptr)
			m->SetMaterial(material);
	}
	GameObjects.push_back(obj);

	engine->Start();
}