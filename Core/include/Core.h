#ifndef _CORE_H
#define _CORE_H

#include "Common.h"
#include "GameObject.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Mesh.h"
#include "DirectionalLight.h"
#include "Input.h"

class Core
{
public:
	bool lockCursor;
	bool lighting;
	int WIDTH;
	int HEIGHT;
	Core(int width, int height);
	~Core();

	void Start();
	void Input(SDL_Event* e);
	void Update();
	void Render();
	void UpdateScreen();

private:
	SDL_Window* window;
	SDL_GLContext context;

	int count = 0;

	void RenderGameObjects(std::shared_ptr<GameObject> g);
};

#endif