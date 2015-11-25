#ifndef _CORE_H
#define _CORE_H

#include "Common.h"
#include "GameObject.h"
#include "Component.h"
#include "Scene.h"

class Core
{
public:
	int width;
	int height;

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