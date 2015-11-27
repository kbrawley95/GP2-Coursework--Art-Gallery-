#ifndef _CORE_H
#define _CORE_H

#include "Common.h"
#include "GameObject.h"
#include "Camera.h"
#include "Scene.h"
#include "TextureLoader.h"

class Core
{
public:
	int WIDTH;
	int HEIGHT;
	Core(int width, int height);
	~Core();

	void Start();
	void Input(SDL_Event* e);
	void Update();
	void Render();

private:
	SDL_Window* window;
	SDL_GLContext context;
};

#endif