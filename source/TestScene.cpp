#include "../include/TestScene.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
	
}

void TestScene::init()
{
	addGameObjectToScene(new GameObject("Ship", ".\\res\\arwing.obj", TextureManager::getTextureManager()->getTexture("Arwing"), ShaderManager::getShaderManager()->getShader("Phong")));
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
		getGameObject("Ship")->getTransform()->GetRot().y += 0.1;
	}

	camera->rotateY(camera->getSensitivity() * display->getMouseDifX());
}