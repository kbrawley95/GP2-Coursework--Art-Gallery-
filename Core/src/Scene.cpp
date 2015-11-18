#include "Scene.h"

Scene::Scene(Camera* camera)
{
	Scene::camera = new GameObject();
	Scene::camera->components.push_back(camera);
}

Scene::~Scene()
{

}