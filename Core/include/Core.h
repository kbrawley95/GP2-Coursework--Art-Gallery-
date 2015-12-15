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

	//FBO Post Processing
	GLuint FBOTexture;
	GLuint FBODepthBuffer;
	GLuint frameBufferObject;
	GLuint frameBufferVAO;
	GLuint frameBufferVBO;
	std::shared_ptr<Material> frambeBufferShader;

	//FBO Shadows
	GLuint ShadowDepthTexture;
	GLuint shadowFrameBufferObject;
	std::shared_ptr<Material> shadowFBOShader;

	vec2 screenResolution = vec2(WIDTH, HEIGHT);

	int count = 0;
	int fpsCounter = 0;
	int fpsTimer = 0;

	int lastTicks = 0;
	int totalTime = 0;

	int triangleCounter = 0;

	void Update();
	void Render();
	void Input(SDL_Event* e);
	void CreateFramebuffer();
	void RenderGameObjects(std::shared_ptr<GameObject> g);
	void RenderPostQuad();
	void RenderShadowMap();
};

#endif