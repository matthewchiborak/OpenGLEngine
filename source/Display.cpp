#include "../include/Display.h"

Display::Display(int width, int height, const std::string& title)
{
	//Init SDL DONT DO THS IF DOING MORE THAN DISPLAY WINDOW
	//Safe to do if just for windowing
	SDL_Init(SDL_INIT_EVERYTHING);

	//CREATES 2 to 8th power shades of red. 8 is a good value. 
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	//Data that is allocated for a single pixel. 8*4; THis is a mimimum. Wont get exactly8
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	//Allcoate space for the zbuffer to ensure proper drawing
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

	//Allocate space for 2 windows for second areea to draw in.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Create window
	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	
	//Need to create context to access window from GPU instead of from the operating system. 
	m_glContext = SDL_GL_CreateContext(m_window);

	GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		std::cerr << "Glew failed to init\n";
	}

	m_isClosed = false;

	//Enable zbuffering
	glEnable(GL_DEPTH_TEST);

	//Fix the issue of order of rendering (back face culling)
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	for (int i = 0; i < 322; i++) 
	{ // init them all to false
		KEYS[i] = false;
		KEYDOWN[i] = false;
		KEYUP[i] = false;
	}

	//SDL_EnableKeyRepeat(0, 0); // you can configure this how you want, but it makes it nice for when you want to register a key continuously being held down
}

Display::~Display()
{
	//Delete in the reverse order they were created
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Display::Update()
{
	SDL_GL_SwapWindow(m_window);

	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		/*if (e.type == SDL_QUIT)
		{
			m_isClosed = true;
		}*/
		switch (e.type)
		{
			case SDL_QUIT:
				m_isClosed = true;
				break;
			case SDL_KEYDOWN:
				KEYS[e.key.keysym.sym] = true;
				KEYUP[e.key.keysym.sym] = false;
				break;
			case SDL_KEYUP:
				KEYS[e.key.keysym.sym] = false;
				KEYDOWN[e.key.keysym.sym] = false;
				//Reset the keydown bool
				break;
			case SDL_MOUSEMOTION:
				//Store the new mouse position
				mousePrevX = mouseX;
				mousePrevY = mouseY;
				mouseX = e.button.x;
				mouseY = e.button.x;
				break;
			default:
			break;
		}
	}
}

int Display::getMouseDifX()
{
	int result = (mousePrevX - mouseX);

	//Event has been handled
	mousePrevX = mouseX;

	return result;
}
int Display::getMouseDifY()
{
	int result = (mousePrevY - mouseY);

	//Event has been handled
	mousePrevY = mouseY;

	return result;
}

bool Display::isClosed()
{
	return m_isClosed;
}

void Display::clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	//Fill all colours with the clear colour
	//Also clrea the z buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Display::checkKey(int key)
{
	return KEYS[key];
}

bool Display::checkKeyDown(int key)
{
	if (KEYS[key] && !KEYDOWN[key])
	{
		KEYDOWN[key] = true;
		return true;
	}

	return false;
}

bool Display::checkKeyUp(int key)
{
	if (!KEYS[key] && !KEYUP[key])
	{
		KEYUP[key] = true;
		return true;
	}

	return false;
}