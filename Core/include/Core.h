#ifndef _CORE_H
#define _CORE_H

#include "Common.h"
#include "Texture.h"
#include "Mesh.h"

class Core
{
public:
	int width = 800;
	int height = 600;

	Core(int width, int height);
	~Core();

	void StartMainLoop();

private:
	SDL_Window* window;
	SDL_GLContext glcontext;

	void Update();
	void Render();
	void CleanUp();
	void InitOpenGL();
	string GetRendererCapsAsString();
};

void CoreInitialise();
void CoreMainLoop();

#endif
