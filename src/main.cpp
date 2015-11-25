#include "Core.h"

#define SDL_main main
shared_ptr<GameObject> MainCamera;
shared_ptr<GameObject> MainLight;
vector<shared_ptr<GameObject>> GameObjects;

int main(int argc, char *argv[])
{
	Core* engine = new Core(800, 600);

	//Create Camera
	MainCamera = shared_ptr<GameObject>(new GameObject("Main Camera"));
	shared_ptr<Camera> cam = MainCamera->AddComponent<Camera>();
	cam->fov = 90;
	cam->aspect = 1;
	cam->zNear = 0.1f;
	cam->zFar = 100;
	GameObjects.push_back(MainCamera);

	//Create Light
	//MainLight = shared_ptr<GameObject>(new GameObject());
	//MainLight->AddComponent(shared_ptr<Light>(new Light()));

	//Create New Object
	shared_ptr<GameObject> artGalleryModel = shared_ptr<GameObject>(new GameObject("Art Galary Model"));
	//Add a mesh component to store the mesh
	shared_ptr<Mesh> m = artGalleryModel->AddComponent<Mesh>();
	m->LoadFBX(MODEL_PATH + "/Art_Gallery1.fbx");
	//Add a mesh renderer component to render stored mesh
	shared_ptr<MeshRenderer> render = artGalleryModel->AddComponent<MeshRenderer>();
	render->SetMaterial(shared_ptr<Material>(new Material(SHADER_PATH + "/simpleColourVS.glsl", SHADER_PATH + "/simpleColourFS.glsl")));
	//Add object to the list
	GameObjects.push_back(artGalleryModel);

	engine->Start();
}