#include "Scene.h"

Scene::Scene(Camera* camera)
{
	Scene::camera = shared_ptr<GameObject>(new GameObject());
	Scene::camera->components.push_back(camera);

	Scene::light = shared_ptr<GameObject>(new GameObject());
	Scene::light->components.push_back(new Light());
}

Scene::~Scene()
{

}