#ifndef __COREENGINE_H
#define __COREENGINE_H

#include <iostream>
#include <GL/glew.h>
#include <D:/OpenGL2017/SDL2-devel-2.0.5-VC/SDL2-2.0.5/include/SDL.h>

#include "Display.h"
#include "Scene.h"
//#include "GameObject.h"
//#include "Shader.h"
//#include "Mesh.h"
//#include "Texture.h"
//#include "Transform.h"

//#include "Camera.h"
//#include "Time.h"

//#include "Input.h"

//#include "Bitmap.h"
//#include "TextureManager.h"
//#include "ShaderManager.h"
#include "Game.h"


class CoreEngine
{
public:
	CoreEngine();
	~CoreEngine();

	static CoreEngine* getCoreEngine();

	void init(int width, int height, double frameRate, Game* game, std::string name);

	void loadScene(std::string name, std::string fileName);
	void loadScene(Scene* newScene, std::string name, std::string fileName);
	Scene* getScene(std::string name);

	void run();

	void setIsRunning(bool value);
	bool getIsRunning();

private:
	static CoreEngine* s_instance;
	Display* display;
	int width;
	int height;
	std::string name;

	bool isRunning;

	int currentScene;
	std::vector<Scene*> scenes;
	Game* game;
	double FRAME_CAP;
	double frameTime;
};

#endif