#include "../include/TestScene.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
	
}

void TestScene::init()
{
	addGameObjectToScene(new GameObject("Ship", ".\\res\\monkey3.obj", TextureManager::getTextureManager()->getTexture("Arwing"), ShaderManager::getShaderManager()->getShader("Phong")));
}

void TestScene::earlyUpdate()
{

}

void TestScene::lateUpdate()
{
	
}

void TestScene::input(Display* display)
{
	if (display->checkKey(SDLK_a))
	{
		std::cout << "Test\n";
	}

	camera->rotateY(camera->getSensitivity() * display->getMouseDifX());
}