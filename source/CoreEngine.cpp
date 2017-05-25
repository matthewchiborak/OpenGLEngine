#include "../include/CoreEngine.h"

CoreEngine* CoreEngine::s_instance = 0;

CoreEngine::CoreEngine()
{
	currentScene = 0;
	isRunning = true;
}

CoreEngine::~CoreEngine()
{
	if (display != NULL)
	{
		delete display;
	}

	if (s_instance)
	{
		delete s_instance;
	}
}

CoreEngine * CoreEngine::getCoreEngine()
{
	if (!s_instance)
	{
		s_instance = new CoreEngine();
	}

	return s_instance;
}

void CoreEngine::init(int width, int height, double frameRate, Game* game, std::string name)
{
	this->width = width;
	this->height = height;
	this->game = game;
	this->FRAME_CAP = frameRate;
	frameTime = 1 / frameRate;

	display = new Display(width, height, name);
}

void CoreEngine::loadScene(std::string name, std::string fileName)
{
	Scene* newScene = new Scene(name, fileName, width, height);
	scenes.push_back(newScene);
	newScene->init();
}

void CoreEngine::loadScene(Scene* newScene, std::string name, std::string fileName)
{
	newScene->assignInfo(name, width, height);
	scenes.push_back(newScene);
	//newScene->init();
	//newScene->baseInit(name, fileName, width, height);
}

Scene* CoreEngine::getScene(std::string name)
{
	for (int i = 0; i < scenes.size(); i++)
	{
		if (scenes.at(i)->getName() == name)
		{
			return scenes.at(i);
		}
	}

	return NULL;
}

void CoreEngine::run()
{
	float counter = 0.0f;

	//Event for input
	SDL_Event event;

	//Fixed frame rate
	//static double FRAME_CAP = 5000.0;
	//static double FRAME_CAP = 60.0;
	long lastTime = Time::getTime();
	double unprocessedTime = 0; //Keep track of time still needed to be processed to update the game
	//double frameTime = 1.0 / FRAME_CAP;
	int frames = 0;
	long frameCounter = 0;

	//Start the scene
	scenes.at(currentScene)->init();

	while (!display->isClosed() && isRunning)
	{
		//Fixed Frame rate
		long startTime = Time::getTime();
		long passedTime = startTime - lastTime;
		lastTime = startTime;
		frameCounter += passedTime;

		//UPDATE GAME
		display->clear(0.0f, 0.0f, 0.0f, 0.0f);

		scenes.at(currentScene)->update(passedTime);
		scenes.at(currentScene)->input(display, passedTime);
		RenderingEngine::getRenderingEngine()->render(scenes.at(currentScene)->getRootObject(), scenes.at(currentScene)->getCamera());
		display->Update();

		counter += 0.01f;
		frames++;

		//Output the framerate
		if (frameCounter >= Time::SECOND)
		{
			std::cout << "FPS: " << frames << "\n";
			frames = 0;
			frameCounter = 0;
		}
	}

	////Delete the scenes
	for (int i = 0; i < scenes.size(); i++)
	{
		if (scenes.at(i) != NULL)
		{
			delete scenes.at(i);
		}
	}
}

void CoreEngine::setIsRunning(bool value)
{
	isRunning = value;
}
bool CoreEngine::getIsRunning()
{
	return isRunning;
}