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
	//artGalleryModel->components.push_back(new MeshRenderer());

	engine.Start();


	shared_ptr<Shader> vs = shared_ptr<Shader>(new Shader(SHADER_PATH + "/shit.vs", Shader::SHADER_TYPE::VERTEX_SHADER));
	shared_ptr<Shader> fs = shared_ptr<Shader>(new Shader(SHADER_PATH + "/shit.fs", Shader::SHADER_TYPE::FRAGMENT_SHADER));
	shared_ptr<Material> blue = shared_ptr<Material>(new Material(vs, fs));
	shared_ptr<MeshRenderer> mesh = shared_ptr<MeshRenderer>(new MeshRenderer(blue));



	return 0;
}