#include "Core.h"

#define SDL_main main
shared_ptr<GameObject> MainCamera;
shared_ptr<GameObject> MainLight;
vector<shared_ptr<GameObject>> GameObjects;

int main(int argc, char *argv[])
{
	Core* engine = new Core(800, 600);


	
	engine->Start();
}