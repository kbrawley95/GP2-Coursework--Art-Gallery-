#include "Core.h"

Core::Core(int width, int height)
{
	cout << "Starting up" << endl;
	//Set width and height for the window
	Core::width = width;
	Core::height = height;

	//Change working directory
#ifdef _WIN32
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	//move into a string(just makes it easier
	string exeFullFilename(buffer);
	cout << "Exe Path & Filename " << exeFullFilename << endl;
	//now stripout the exe
	string exeDirectory = exeFullFilename.substr(0, exeFullFilename.find_last_of("\\"));
	cout << "Exe Directory " << exeDirectory << endl;
	SetCurrentDirectory(exeDirectory.c_str());
#endif
	cout << "Working directory changed" << endl;

	// init everyting - SDL, if it is nonzero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init " << SDL_GetError() << std::endl;
		return;
	}

	cout << "SDL initialised" << endl;

	//Init SDL_Image
	int	imageInitFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int	returnInitFlags = IMG_Init(imageInitFlags);
	if (((returnInitFlags)&	(imageInitFlags)) != imageInitFlags)	{

		cout << "ERROR	SDL_Image	Init	" << IMG_GetError() << endl;
	}

	if (TTF_Init() == -1)	{
		std::cout << "ERROR	TTF_Init:	" << TTF_GetError();
	}

	cout << "SDL_Image initialised" << endl;

	// Request opengl 4.1 context, Core Context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	cout << "Open GL version set to 4.1" << endl;

	//Create a window
	window = SDL_CreateWindow(
		"SDL",             // window title
		SDL_WINDOWPOS_CENTERED,     // x position, centered
		SDL_WINDOWPOS_CENTERED,     // y position, centered
		640,                        // width, in pixels
		480,                        // height, in pixels
		SDL_WINDOW_OPENGL           // flags
		);

	// Create an OpenGL context associated with the window.
	glContext = SDL_GL_CreateContext(window);

	cout << "SDL window created" << endl;

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		//Problem: glewInit failed, something is seriously wrong.
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
	}

	cout << "GLEW initalised" << endl;

	// Smooth shading
	glShadeModel(GL_SMOOTH);

	//clear the background to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Clear the depth buffer
	glClearDepth(1.0f);

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);

	//The depth test to go
	glDepthFunc(GL_LEQUAL);

	//Turn on best perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	cout << "Open GL setup complete" << endl;

	//Set our viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	cout << "Viewport setup complete" << endl;
}

Core::~Core()
{
	cout << "Cleaning up" << endl;
	// clean up, reverse order!!!
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void Core::Start()
{
	for (auto i = GameObjects.begin(); i != GameObjects.end(); ++i)
	{
		for (auto j = (*i)->GetComponents().begin(); j != (*i)->GetComponents().end(); ++j)
		{
			(*j)->Start();
		}
	}
	cout << "Game Main Loop Started" << endl;
	//Value to hold the event generated by SDL
	SDL_Event event;
	//Game Loop
	bool run = true; while (run)
	{
		previousTime = currentTime;
		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - previousTime) / 1000.0f;

		//While we still have events in the queue
		while (SDL_PollEvent(&event))
		{
			//Get event type
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
			{
				//set our boolean which controls the loop to false
				run = false;
			}

			Input(&event);
		}
		//init Scene
		Update();
		//render
		Render();
		//Call swap so that our GL back buffer is displayed
		SDL_GL_SwapWindow(window);
	}
}

void Core::Input(SDL_Event* e)
{
	for (auto i = GameObjects.begin(); i != GameObjects.end(); ++i)
	{
		for (auto j = (*i)->GetComponents().begin(); j != (*i)->GetComponents().end(); ++j)
		{
			(*j)->Input(e);
		}
	}
}

void Core::Update()
{
	for (auto i = GameObjects.begin(); i != GameObjects.end(); ++i)
	{
		for (auto j = (*i)->GetComponents().begin(); j != (*i)->GetComponents().end(); ++j)
		{
			(*j)->Update();
		}
	}
}

void Core::Render()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//Set the clear colour(background)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto i = GameObjects.begin(); i != GameObjects.end(); ++i)
	{
		for (auto j = (*i)->GetComponents().begin(); j != (*i)->GetComponents().end(); ++j)
		{
			(*j)->Render();
		}
	}
}