#ifndef _CORE_H
#define _CORE_H

#include "Common.h"
#include "Scene.h"
#include "Mesh.h"

class Core
{
public:
	int width = 800;
	int height = 600;
	Scene* scene;

	Core(int width, int height);
	~Core();

	void Start();

private:
	SDL_Window* window;
	SDL_GLContext glContext;

	void Render();
	void Update();
	void Input(SDL_Event* e);
};

#endif