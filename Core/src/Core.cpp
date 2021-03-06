#include "Core.h"

Core::Core(int width, int height)
{
	std::cout << "Starting up" << std::endl;
	lockCursor = false;
	debugMode = true;
	culling = true;
	WIDTH = width;
	HEIGHT = height;

	//SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init " << SDL_GetError() << std::endl;
		return;
	}
	std::cout << "SDL Initilized" << std::endl;

	//SDL_Image
	int imageInitFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int returnInitFlags = IMG_Init(imageInitFlags);
	if ((returnInitFlags & imageInitFlags) != imageInitFlags)
	{
		std::cout << "ERROR SDL_Image " << IMG_GetError() << std::endl;
		return;
	}
	std::cout << "SDL_Image Initilized" << std::endl;

	if (TTF_Init() != 0)
	{
		std::cout << "ERROR TTF_Init" << std::endl;
		return;
	}
	std::cout << "SDL_TTF Initilized" << std::endl;

	//Request Open GL 4.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	std::cout << "Open GL version set to 4.1" << std::endl;

	//Create Window
	window = SDL_CreateWindow(
		"Core Engine",               // window title
		SDL_WINDOWPOS_CENTERED,      // x position, centered
		SDL_WINDOWPOS_CENTERED,      // y position, centered
		WIDTH,                       // width, in pixels
		HEIGHT,                      // height, in pixels
		SDL_WINDOW_OPENGL            // flags
		);

	//Create Context
	context = SDL_GL_CreateContext(window);
	std::cout << "Window & Context Initilized" << std::endl;

	//Setup Open GL
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "GLEW Error " << glewGetErrorString(err) << std::endl;
		return;
	}
	std::cout << "GLEW Initilized" << std::endl;

	//Smooth shading
	glShadeModel(GL_SMOOTH);
	
	//Set clear color to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Clear depth buffer
	glClearDepth(1.0f);

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);

	//the depth test to go
	glDepthFunc(GL_LEQUAL);

	//Enable Culling
	glEnable(GL_CULL_FACE);

	//Back face culling
	glCullFace(GL_BACK);

	//GL_CCW for counter clock-wise
	glFrontFace(GL_CCW);

	//Turn on the best perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//setup viewport
	glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);

	std::cout << "Open GL setup complete." << std::endl;

	//Change working directory
	std::cout << "Changing working directory" << std::endl << std::endl;
#ifdef _WIN32
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::string exeFullFilename = std::string(buffer);
	std::string exeDirectory = exeFullFilename.substr(0, exeFullFilename.find_last_of("\\"));
	SetCurrentDirectory(exeDirectory.c_str());
#endif
}

Core::~Core()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Core::Start()
{
	//Setup frame buffer for post processing
	std::cout << "Setting up frame buffers for post processing" << std::endl;
	CreateFramebuffer();

	//Load Font
	std::string text = FONT_PATH + "Holstein.dds";
	font = std::shared_ptr<Text2D>(new Text2D(text.c_str()));
	FPS = 0;
	std::cout << std::endl << "[Main Loop Started]" << std::endl;

	

	for (auto i = GameObjects.begin(); i != GameObjects.end(); ++i)
	{
		for (std::shared_ptr<Component> j : (*i)->GetComponents())
			j->Start();
	
		for (std::shared_ptr<GameObject> j : (*i)->GetChildren())
		{
			for (std::shared_ptr<Component> k : j->GetComponents())
				k->Start();
		}
	}
	SDL_Event events;

	run = true;
	while (run)
	{
		while (SDL_PollEvent(&events))
		{
			if (events.type == SDL_QUIT || events.type == SDL_WINDOWEVENT_CLOSE)
				run = false;

			if (events.type == SDL_KEYDOWN)
			{
				switch (events.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					run=false;
					break;

				case SDLK_TAB:
					ChangeResolution(1920, 1080, true);
					break;
				case SDLK_F1:
					debugMode = !debugMode;
					break;
				}
			}
			Input(&events);
		}

		Update();

		Render();


		SDL_GL_SwapWindow(window);
	}
}

std::shared_ptr<GameObject> Core::Instantiate()
{
	std::shared_ptr<GameObject> g = std::shared_ptr<GameObject>(new GameObject());
	GameObjects.push_back(g);
	return g;
}

void Core:: ChangeResolution(int w, int h, bool fullscreen)
{
	WIDTH = w;
	HEIGHT = h;
	MainCamera->ChangeRatio(w / h);
	SDL_SetWindowSize(window, WIDTH, HEIGHT);
	glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);
	if (fullscreen)
		SDL_SetWindowFullscreen(window, SDL_TRUE);
	else
		SDL_SetWindowFullscreen(window, SDL_FALSE);	
}

void Core::SetSkyBox(std::string front, std::string back, std::string left, std::string right, std::string top, std::string bottom)
{
	SkyBox = std::shared_ptr<GameObject>(new GameObject("SkyBox"));
	SkyBox->transform.position = Vector3(0, 0, -40);
	std::shared_ptr<Mesh> skyboxMesh = SkyBox->AddComponent<Mesh>();
	skyboxMesh->vertices.clear();
	skyboxMesh->indices.clear();
	for (int i = 0; i < numberOfCubeVerts; i++)
		skyboxMesh->vertices.push_back(cubeVerts[i]);
	for (int i = 0; i < numberOfCubeIndices; i++)
		skyboxMesh->indices.push_back(cubeIndices[i]);

	skyboxMesh->SetMaterial(std::shared_ptr<Material>(new Material(SHADER_PATH + "skyVS.glsl", SHADER_PATH + "skyFS.glsl")));
	skyboxMesh->GetMaterial()->SetCubeMapTextures(left, right, top, bottom, front, back);
	skyboxMesh->GenerateBuffers();
}


//PRIVATE

void Core::Input(SDL_Event* e)
{
	for (auto i = GameObjects.begin(); i != GameObjects.end(); ++i)
		for (std::shared_ptr<Component> j : (*i)->GetComponents())
			j->Input(e);

	if (e->type == SDL_KEYDOWN)
		keysPressed[e->key.keysym.sym] = true;
	if (e->type == SDL_KEYUP)
		keysPressed[e->key.keysym.sym] = false;

	if (lockCursor)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	else
		SDL_SetRelativeMouseMode(SDL_FALSE);

}

void Core::Update()
{	
	for (auto i = GameObjects.begin(); i != GameObjects.end(); ++i)
	{
		for (std::shared_ptr<Component> j : (*i)->GetComponents())
			j->Update();

		for (std::shared_ptr<GameObject> j : (*i)->GetChildren())
		{
			for (std::shared_ptr<Component> k : j->GetComponents())
				k->Start();
		}
	}

	
	//Camera & Skybox
	MainCamera->Update();
	SkyBox->transform.position = MainCamera->transform.position;

	//Mouse
	int x, y;
	SDL_GetMouseState(&x, &y);
	mousePosition = Vector2(static_cast<float>(x), static_cast<float>(y));
	SDL_GetRelativeMouseState(&x, &y);
	mouseDelta = Vector2(x, y);

	//Time
	lastTicks = currentTime;
	prevTime = currentTime;
	currentTime = SDL_GetTicks();
	deltaTime = (currentTime - prevTime) / 1000.0f;
	totalTime += deltaTime;

	//Calculate FPS
	if (fpsTimer < currentTime)
	{
		FPS = fpsCounter;
		fpsTimer = currentTime + 1000;
		fpsCounter = 0;
	}
	else
		fpsCounter++;
}

void Core::CreateFramebuffer()
{
	//Create post processing FBO
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &FBOTexture);
	glBindTexture(GL_TEXTURE_2D, FBOTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);


	glGenRenderbuffers(1, &FBODepthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, FBODepthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, WIDTH, HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glGenFramebuffers(1, &frameBufferObject);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FBOTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, FBODepthBuffer);

	GLenum status;
	if ((status = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Issue with Framebuffers" << std::endl;
	}
	float vertices[] = {
		-1, -1,
		1, -1,
		-1, 1,
		1, 1,

	};

	glGenVertexArrays(1, &frameBufferVAO);
	glBindVertexArray(frameBufferVAO);

	glGenBuffers(1, &frameBufferVBO);
	glBindBuffer(GL_ARRAY_BUFFER, frameBufferVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,					// attribute
		2,                  // number of elements per vertex, here (x,y)
		GL_FLOAT,           // the type of each element
		GL_FALSE,           // take our values as-is
		0,                  // no extra data between each position
		0                   // offset of first element
		);

	std::string vsPath = SHADER_PATH + "simplePostProcessVS.glsl";
	std::string fsPath = SHADER_PATH + "simplePostProcessFS.glsl";
	frambeBufferShader = std::shared_ptr<Material>(new Material(vsPath, fsPath));

	//Create Shadow Mapping FBO
	/*
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &ShadowDepthTexture);
	glBindTexture(GL_TEXTURE_2D, ShadowDepthTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

	glGenRenderbuffers(1, &shadowFrameBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, shadowFrameBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, 1024, 1024);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, shadowFrameBufferObject);

	if ((status = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Issue with Framebuffers" << std::endl;
	}

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,					// attribute
		3,                  // number of elements per vertex, here (x,y)
		GL_FLOAT,           // the type of each element
		GL_FALSE,           // take our values as-is
		0,                  // no extra data between each position
		0                   // offset of first element
		);

	vsPath = SHADER_PATH + "lightmapGeneratorVS.glsl";
	fsPath = SHADER_PATH + "lightmapGeneratorFS.glsl";
	shadowFBOShader = std::shared_ptr<Material>(new Material(vsPath, fsPath));
	*/
}

//Main Render Function
void Core::Render()
{
	//RenderShadowMap();

	//Render Scene
	triangleCounter = 0;
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDepthMask(GL_FALSE);
	RenderGameObjects(SkyBox);
	glDepthMask(GL_TRUE);

	for (auto i = GameObjects.begin(); i != GameObjects.end(); ++i)
	{
		RenderGameObjects((*i));

		for (std::shared_ptr<Component> K : (*i)->GetComponents())
			K->PostRender();
	}

	//Debug UI
	if (debugMode)
	{
		std::string fps = "FPS: " + std::to_string(FPS);
		font->Render(fps.c_str(), 0, 0, 24);
		std::string triangles = "Triangles: " + std::to_string(triangleCounter);
		font->Render(triangles.c_str(), 0, 30, 24);
	}

	RenderPostQuad();
}

//Render each game object & all of its children
void Core::RenderGameObjects(std::shared_ptr<GameObject> g)
{
	std::shared_ptr<Mesh> m = g->GetComponent<Mesh>();
	if (m != nullptr)
	{
		if (culling)
		{
			if (!MainCamera->FrustumCulling(glm::vec3(g->transform.GetWorldMatrix()[3])))
				return;
		}

		glUseProgram(m->GetMaterial()->GetShader());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m->GetMaterial()->GetTexture());

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m->GetMaterial()->GetCubeMap());

		GLint MVPLocation = glGetUniformLocation(m->GetMaterial()->GetShader(), "MVP");
		GLint texture0Location = glGetUniformLocation(m->GetMaterial()->GetShader(), "texture0");
		GLint cubeTexture = glGetUniformLocation(m->GetMaterial()->GetShader(), "cubeTexture");
		GLint modelLocation = glGetUniformLocation(m->GetMaterial()->GetShader(), "Model");
		GLint cameraPosition = glGetUniformLocation(m->GetMaterial()->GetShader(), "cameraPosition");


		GLint ambientLightColourLocation = glGetUniformLocation(m->GetMaterial()->GetShader(), "ambientLightColour");
		GLint ambientMaterialColourLocation = glGetUniformLocation(m->GetMaterial()->GetShader(), "ambientMaterialColour");

		GLint diffuseLightColourLocation = glGetUniformLocation(m->GetMaterial()->GetShader(), "diffuseLightColour");
		GLint diffuseMaterialLocation = glGetUniformLocation(m->GetMaterial()->GetShader(), "diffuseMaterialColour");
		GLint lightDirectionLocation = glGetUniformLocation(m->GetMaterial()->GetShader(), "lightDirection");

		GLint specularLightColourLocation = glGetUniformLocation(m->GetMaterial()->GetShader(), "specularLightColour");
		GLint specularMaterialLocation = glGetUniformLocation(m->GetMaterial()->GetShader(), "specularMaterialColour");
		GLint specularPowerLocation = glGetUniformLocation(m->GetMaterial()->GetShader(), "specularPower");			

		glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(g->GetMVPMatrix()));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(g->transform.GetWorldMatrix()));
		glUniform3fv(cameraPosition, 1, glm::value_ptr(MainCamera->transform.position.ConvertToVec3()));
		glUniform1i(texture0Location, 0);
		glUniform1i(cubeTexture, 1);

		glUniform4fv(ambientLightColourLocation, 1, value_ptr(MainLight->ambientLightColor.ConvertToVec4()));
		glUniform4fv(ambientMaterialColourLocation, 1, value_ptr(m->GetMaterial()->ambientMaterial.ConvertToVec4()));

		glUniform4fv(diffuseLightColourLocation, 1, value_ptr(MainLight->diffuseLightColor.ConvertToVec4()));
		glUniform4fv(diffuseMaterialLocation, 1, value_ptr(m->GetMaterial()->diffuseMaterial.ConvertToVec4()));
		glUniform3fv(lightDirectionLocation, 1, value_ptr(MainLight->direction.ConvertToVec3()));

		glUniform4fv(specularLightColourLocation, 1, value_ptr(MainLight->specularLightColor.ConvertToVec4()));
		glUniform4fv(specularMaterialLocation, 1, value_ptr(m->GetMaterial()->specularMaterial.ConvertToVec4()));
		glUniform1f(specularPowerLocation, m->GetMaterial()->specularPower);

		//Draw Shit
		glBindVertexArray(m->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m->VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->EBO);

		glDrawElements(GL_TRIANGLES, m->indices.size(), GL_UNSIGNED_INT, 0);
		triangleCounter += m->indices.size() / 3;
	}

	for (std::shared_ptr<GameObject> j : g->GetChildren())
	{
		RenderGameObjects(j);

		for (std::shared_ptr<Component> K : g->GetComponents())
			K->PostRender();
	}
}

//Post Processing
void Core::RenderPostQuad()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//Set the clear colour(background)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(frambeBufferShader->GetShader());

	GLint textureLocation = glGetUniformLocation(frambeBufferShader->GetShader(), "texture0");
	GLint timeLocation = glGetUniformLocation(frambeBufferShader->GetShader(), "time");
	GLint resolutionLocation = glGetUniformLocation(frambeBufferShader->GetShader(), "resolution");

	glUniform1f(timeLocation, totalTime);
	glUniform2fv(resolutionLocation, 1, value_ptr(screenResolution));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, FBOTexture);
	glUniform1i(textureLocation, 0);

	glBindVertexArray(frameBufferVAO);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

//Render Shadow Map
void Core::RenderShadowMap()
{
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFrameBufferObject);
	//Set the clear colour(background)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//clear the colour and depth buffer
	glClear(GL_DEPTH_BUFFER_BIT);

	glUseProgram(shadowFBOShader->GetShader());

	GLint MVPLocation = glGetUniformLocation(shadowFBOShader->GetShader(), "MVP");
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MainLight->projection));

	glDrawBuffer(GL_BACK);
	glBindTexture(GL_TEXTURE_2D, ShadowDepthTexture);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}