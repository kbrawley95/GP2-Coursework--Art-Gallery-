#include "Scene.h"

Scene::Scene(shared_ptr<Camera> camera)
{
	Scene::camera = shared_ptr<GameObject>(new GameObject());
	Scene::camera->AddComponent(camera);

	Scene::light = shared_ptr<GameObject>(new GameObject());
	Scene::light->AddComponent(shared_ptr<Light>(new Light()));
}

Scene::~Scene()
{

}