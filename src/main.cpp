#include "Core.h"

#define SDL_main main

int main(int argc, char *argv[])
{
	//Start Engine
	Core engine = Core(800, 600);

	//Create New Scene & Setup Camera
	Scene* artGalary = new Scene(new Camera(90, 1, 0.1f, 1000));
	engine.scene = artGalary;

	//Create New Object
	GameObject* artGalaryModel = new GameObject();
	//Add a mesh component to store the mesh
	artGalaryModel->components.push_back(new Mesh(MODEL_PATH + "/Art Gallery.fbx"));
	//Add a mesh renderer component to render stored mesh


	engine.Start();

	return 0;
}