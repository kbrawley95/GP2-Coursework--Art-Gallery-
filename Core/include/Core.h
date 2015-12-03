#ifndef _CORE_H
#define _CORE_H

#include "Common.h"
#include "GameObject.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Mesh.h"
#include "DirectionalLight.h"

class Core
{
public:
	bool lighting;
	int WIDTH;
	int HEIGHT;
	Core(int width, int height);
	~Core();

	void Start();
	void Input(SDL_Event* e);
	void Update();
	void Render();
	void RenderSkyBox();

private:
	SDL_Window* window;
	SDL_GLContext context;

	void RenderGameObjects(std::shared_ptr<GameObject> g);
};

#endif