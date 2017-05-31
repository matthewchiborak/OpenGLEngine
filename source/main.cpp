#include <iostream>
#include <GL/glew.h>
#include <D:/OpenGL2017/SDL2-devel-2.0.5-VC/SDL2-2.0.5/include/SDL.h>

#include "../include/CoreEngine.h"
#include "../include/TestScene.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv)
{
	//Game or scene? Should change it so the game has scenes???
	CoreEngine::getCoreEngine()->init(WIDTH, HEIGHT, 30, "Hello world!!!");

	TextureManager::getTextureManager()->loadTexture("Arwing", ".\\res\\body.png");

	MeshManager::getMeshManager()->loadMesh("Arwing", ".\\res\\arwing.obj");

	Scene* testScene = new TestScene();
	CoreEngine::getCoreEngine()->loadScene(testScene, "Test", "Test");

	CoreEngine::getCoreEngine()->run();
	
	return 0;
}