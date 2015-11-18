#include "Core.h"

#define SDL_main main

int main(int argc, char *argv[])
{
	//Start Engine
	Core engine = Core(800, 600);

	//Create New Scene & Setup Camera
	Scene* artGallery = new Scene(new Camera(90, 1, 0.1f, 1000));
	engine.scene = artGallery;

	//Create New Object
	GameObject* artGalleryModel = new GameObject();
	//Add a mesh component to store the mesh
	artGalleryModel->components.push_back(new Mesh(MODEL_PATH + "/Art Gallery.fbx"));
	//Add a mesh renderer component to render stored mesh
	artGalleryModel->components.push_back(new MeshRenderer());

	engine.Start();

	return 0;
}