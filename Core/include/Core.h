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
#include "Time.h"
#include "Cube.h"
#include "text2D.h"

class Core
{
public:
	bool lockCursor;
	bool debugMode;
	bool culling;
	bool postProcessing;
	std::shared_ptr<Text2D> font;
	int WIDTH;
	int HEIGHT;
	int FPS;
	Core(int width, int height);
	~Core();

	bool GetRun()
	{
		return run;
	}

	void Start();
	void ChangeResolution(int w, int h, bool fullscreen);
	std::shared_ptr<GameObject> Instantiate();
	void SetSkyBox(std::string front, std::string back, std::string left, std::string right, std::string top, std::string bottom);

private:
	SDL_Window* window;
	SDL_GLContext context;
	int currentTime;
	int prevTime;
	bool run;

	//for Framebuffer
	GLuint FBOTexture;
	GLuint FBODepthBuffer;
	GLuint frameBufferObject;
	GLuint frameBufferVAO;
	GLuint frameBufferVBO;
	std::shared_ptr<Material> frambeBufferShader;

	int count = 0;
	int fpsCounter = 0;
	int fpsTimer = 0;

	int triangleCounter = 0;

	void RenderGameObjects(std::shared_ptr<GameObject> g);
	void Update();
	void Render();
	void Input(SDL_Event* e);
	void CreateFramebuffer();
};

#endif