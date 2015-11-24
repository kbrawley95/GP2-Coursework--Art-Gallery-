#include "Core.h"

#define SDL_main main

int main(int argc, char *argv[])
{
	//Start Engine
	Core engine = Core(800, 600);

	//Create New Scene & Setup Camera
	Scene* artGallery = new Scene(shared_ptr<Camera>(new Camera(90, 1, 0.1f, 1000)));
	engine.scene = artGallery;

	//Create New Object
	shared_ptr<GameObject> artGalleryModel = shared_ptr<GameObject>(new GameObject());
	//Add a mesh component to store the mesh
	artGalleryModel->AddComponent(shared_ptr<Mesh>(new Mesh(MODEL_PATH + "/Art Gallery.fbx")));
	//Add a mesh renderer component to render stored mesh
	shared_ptr<MeshRenderer> render = shared_ptr<MeshRenderer>(new MeshRenderer());
	render->SetMaterial(shared_ptr<Material>(new Material(SHADER_PATH + "simpleColourVS.glsl", SHADER_PATH + "simpleColourFS.glsl")));
	artGalleryModel->AddComponent(render);
	
	artGallery->gameObjects.push_back(artGalleryModel);

	engine.Start();

	return 0;
}