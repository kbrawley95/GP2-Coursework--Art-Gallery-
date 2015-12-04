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
	{
		for (std::shared_ptr<Component> j : (*i)->GetComponents())
			j->Update();

		for (std::shared_ptr<GameObject> j : (*i)->GetChildren())
		{
			for (std::shared_ptr<Component> k : j->GetComponents())
				k->Start();
		}
	}

	MainCamera->Update();
	SkyBox->transform.position = MainCamera->transform.position;
}

void Core::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDepthMask(GL_FALSE);
	RenderGameObjects(SkyBox);
	glDepthMask(GL_TRUE);

	for (auto i = GameObjects.begin(); i != GameObjects.end(); ++i)
	{
		RenderGameObjects((*i));
		for (std::shared_ptr<GameObject> j : (*i)->GetChildren())
		{
			RenderGameObjects(j);

			for (std::shared_ptr<Component> K : (*i)->GetComponents())
				K->PostRender();
		}

		for (std::shared_ptr<Component> K : (*i)->GetComponents())
			K->PostRender();
	}
}

void Core::RenderGameObjects(std::shared_ptr<GameObject> g)
{
	std::shared_ptr<Mesh>m = g->GetComponent<Mesh>();
	if (m != nullptr)
	{
		glUseProgram(m->GetMaterial()->GetShader());

		GLint MVPLocation = glGetUniformLocation(m->GetMaterial()->GetShader(), "MVP");
		GLint texture0Location = glGetUniformLocation(m->GetMaterial()->GetShader(), "texture0");
		GLint cubeTexture = glGetUniformLocation(m->GetMaterial()->GetShader(), "cubeTexture");

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m->GetMaterial()->GetTexture());

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m->GetMaterial()->GetCubeMap());

		glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(g->GetMVPMatrix()));
		glUniform1i(texture0Location, 0);
		glUniform1i(cubeTexture, 1);


		if (lighting)
		{
			GLint ambientLightColourLocation = glGetUniformLocation(m->GetMaterial()->GetShader(), "ambientLightColour");
			GLint ambientMaterialColourLocation = glGetUniformLocation(m->GetMaterial()->GetShader(), "ambientMaterialColour");

			GLint diffuseLightColourLocation = glGetUniformLocation(m->GetMaterial()->GetShader(), "diffuseLightColour");
			GLint diffuseLightMaterialLocation = glGetUniformLocation(m->GetMaterial()->GetShader(), "diffuseMaterialColour");
			GLint lightDirectionLocation = glGetUniformLocation(m->GetMaterial()->GetShader(), "lightDirection");

			GLint specularLightColourLocation = glGetUniformLocation(m->GetMaterial()->GetShader(), "specularLightColour");
			GLint specularLightMaterialLocation = glGetUniformLocation(m->GetMaterial()->GetShader(), "specularMaterialColour");
			GLint specularPowerLocation = glGetUniformLocation(m->GetMaterial()->GetShader(), "specularPower");


			glUniform4fv(ambientLightColourLocation, 1, value_ptr(MainLight->ambientLightColor.ConvertToVec4()));
			glUniform4fv(ambientMaterialColourLocation, 1, value_ptr(m->GetMaterial()->ambientMaterial.ConvertToVec4()));

			glUniform4fv(diffuseLightColourLocation, 1, value_ptr(MainLight->diffuseLightColor.ConvertToVec4()));
			glUniform4fv(diffuseLightMaterialLocation, 1, value_ptr(m->GetMaterial()->diffuseMaterial.ConvertToVec4()));
			glUniform3fv(lightDirectionLocation, 1, value_ptr(MainLight->direction.ConvertToVec3()));

			glUniform4fv(specularLightColourLocation, 1, value_ptr(MainLight->specularLightColor.ConvertToVec4()));
			glUniform4fv(specularLightMaterialLocation, 1, value_ptr(m->GetMaterial()->specularMaterial.ConvertToVec4()));
			glUniform1f(specularPowerLocation, m->GetMaterial()->specularPower);
		}

		glBindVertexArray(m->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m->VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->EBO);

		glDrawElements(GL_TRIANGLES, m->indices.size(), GL_UNSIGNED_INT, 0);
	}
}