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
	MainCamera->transform.position = Vector3(0, 0, 1);
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

	//Create New Object
	shared_ptr<GameObject> artGalleryModel = shared_ptr<GameObject>(new GameObject("Art Galary Model"));
	artGalleryModel->transform.position = Vector3(0 , 0, 0);
	//Add a mesh component to store the mesh
	shared_ptr<Mesh> m = artGalleryModel->AddComponent<Mesh>();
	m->LoadFBX(MODEL_PATH + "/armoredrecon.fbx");
	//Add a mesh renderer component to render stored mesh
	shared_ptr<MeshRenderer> render = artGalleryModel->AddComponent<MeshRenderer>();
	shared_ptr<Material> mat = shared_ptr<Material>(new Material(SHADER_PATH + "/textureVS.glsl", SHADER_PATH + "/textureFS.glsl"));
	mat->SetMainTexture(TEXTURE_PATH+"/armoredrecon_diff.png");
	render->SetMaterial(mat);
	
	//Add object to the list
	GameObjects.push_back(artGalleryModel);

	engine->Start();
}