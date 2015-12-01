#include "Core.h"

Core::Core(int width, int height)
{
	std::cout << "Starting up" << std::endl;
	lighting = true;
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
	std::cout << std::endl << "[Main Loop Started]" << std::endl;

	for (auto i = GameObjects.begin(); i != GameObjects.end(); ++i)
		for (std::shared_ptr<Component> j : (*i)->GetComponents())
			j->Start();

	SDL_Event events;
	bool run = true;
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
				}
			}
			Input(&events);
		}

		Update();

		Render();

		SDL_GL_SwapWindow(window);
	}
}

void Core::Input(SDL_Event* e)
{
	for (auto i = GameObjects.begin(); i != GameObjects.end(); ++i)
		for (std::shared_ptr<Component> j : (*i)->GetComponents())
			j->Input(e);

}

void Core::Update()
{
	for (auto i = GameObjects.begin(); i != GameObjects.end(); ++i)
		for (std::shared_ptr<Component> j : (*i)->GetComponents())
			j->Update();

	MainCamera->Update();
}

void Core::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDepthMask(GL_FALSE);
	RenderSkyBox();
	glDepthMask(GL_TRUE);

	RenderGameObjects();
}

void Core::RenderSkyBox()
{
	std::shared_ptr<Mesh> m = std::shared_ptr<Mesh>(new Mesh());

	GLint cubeTextureLocal = glGetUniformLocation(m->material->GetShader(), "cubeTexture");

	glUniform1i(cubeTextureLocal, 1);
	glGenVertexArrays(1, &m->skyboxVAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, std::shared_ptr<Material>(new Material(SHADER_PATH + "skyVS.glsl", SHADER_PATH + "skyFS.glsl"))->GetCubeMap());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Core::RenderGameObjects()
{
	
	for (auto i = GameObjects.begin(); i != GameObjects.end(); ++i)
	{
		for (std::shared_ptr<Component> j : (*i)->GetComponents())
			j->PostRender();

		std::shared_ptr<Mesh> m = (*i)->GetComponent<Mesh>();
		if (m != nullptr)
		{
			glUseProgram(m->material->GetShader());

			GLint MVPLocation = glGetUniformLocation(m->material->GetShader(), "MVP");
			GLint texture0Location = glGetUniformLocation(m->material->GetShader(), "texture0");


			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m->material->GetTexture());

			glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr((*i)->GetMVPMatrix()));
			glUniform1i(texture0Location, 0);



			if (lighting)
			{
				GLint ambientLightColourLocation = glGetUniformLocation(m->material->GetShader(), "ambientLightColour");
				GLint ambientMaterialColourLocation = glGetUniformLocation(m->material->GetShader(), "ambientMaterialColour");

				GLint diffuseLightColourLocation = glGetUniformLocation(m->material->GetShader(), "diffuseLightColour");
				GLint diffuseLightMaterialLocation = glGetUniformLocation(m->material->GetShader(), "diffuseMaterialColour");
				GLint lightDirectionLocation = glGetUniformLocation(m->material->GetShader(), "lightDirection");

				GLint specularLightColourLocation = glGetUniformLocation(m->material->GetShader(), "specularLightColour");
				GLint specularLightMaterialLocation = glGetUniformLocation(m->material->GetShader(), "specularMaterialColour");
				GLint specularPowerLocation = glGetUniformLocation(m->material->GetShader(), "specularPower");


				glUniform4fv(ambientLightColourLocation, 1, value_ptr(MainLight->ambientLightColor.ConvertToVec4()));
				glUniform4fv(ambientMaterialColourLocation, 1, value_ptr(m->material->ambientMaterial.ConvertToVec4()));

				glUniform4fv(diffuseLightColourLocation, 1, value_ptr(MainLight->diffuseLightColor.ConvertToVec4()));
				glUniform4fv(diffuseLightMaterialLocation, 1, value_ptr(m->material->diffuseMaterial.ConvertToVec4()));
				glUniform3fv(lightDirectionLocation, 1, value_ptr(MainLight->direction.ConvertToVec3()));

				glUniform4fv(specularLightColourLocation, 1, value_ptr(MainLight->specularLightColor.ConvertToVec4()));
				glUniform4fv(specularLightMaterialLocation, 1, value_ptr(m->material->specularMaterial.ConvertToVec4()));
				glUniform1f(specularPowerLocation, m->material->specularPower);
			}

			glBindVertexArray(m->VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m->VBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->EBO);

			glDrawElements(GL_TRIANGLES, m->indices.size(), GL_UNSIGNED_INT, 0);
		}



		for (std::shared_ptr<Component> j : (*i)->GetComponents())
			j->PostRender();
	}

}