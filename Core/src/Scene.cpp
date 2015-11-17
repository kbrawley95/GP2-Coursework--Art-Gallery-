#include "Scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{


}

GameObject* Scene::FindGameObject(string objName)
{
	for (iter = gameObjects.begin(); iter != gameObjects.end(); iter++)
	{
		if ((*iter)->name == objName)
			return (*iter);
	}
}
void Scene::AddGameObject(GameObject* g)
{
	gameObjects.push_back(g);
}
void Scene::RemoveGameObject(GameObject* g)
{
	gameObjects.remove(g);
}