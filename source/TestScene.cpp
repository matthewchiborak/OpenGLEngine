#include "../include/TestScene.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
	
}

void TestScene::init()
{
	//addGameObjectToScene(new GameObject("Ship", ".\\res\\arwing.obj", TextureManager::getTextureManager()->getTexture("Arwing"), ShaderManager::getShaderManager()->getShader("Phong")));
	//Mesh* testMesh = new Mesh(".\\res\\arwing.obj");
	
	//MeshRenderer* testMR = new MeshRenderer(MeshManager::getMeshManager()->getMesh("Arwing"), TextureManager::getTextureManager()->getTexture("Arwing"), ShaderManager::getShaderManager()->getShader("Phong"));
	//root.addComponent(testMR);
	MeshRenderer* testMR = new MeshRenderer(MeshManager::getMeshManager()->getMesh("Arwing"), TextureManager::getTextureManager()->getTexture("Arwing"));
	GameObject* testObject = new GameObject();
	testObject->addComponent(testMR);
	root.addChild(testObject);

	GameObject* testObject2 = new GameObject();
	//MeshRenderer* testMR2 = new MeshRenderer(MeshManager::getMeshManager()->getMesh("Arwing"), TextureManager::getTextureManager()->getTexture("Arwing"), ShaderManager::getShaderManager()->getShader("Phong"));
	MeshRenderer* testMR2 = new MeshRenderer(MeshManager::getMeshManager()->getMesh("Arwing"), TextureManager::getTextureManager()->getTexture("Arwing"));
	testObject2->addComponent(testMR2);
	testObject->addChild(testObject2);
	testObject2->move(Vec9::createVec9(1, 0, 0, 0, 0, 0, 0, 0, 0));

	//Render 
	//testObject->addDirectionalLight(new DirectionalLight(glm::fvec3(1, 0, 0), glm::fvec3(1, 0, 0), 1));
	testObject2->addPointLight(new PointLight(glm::fvec3(0, 1, 0), 10, glm::fvec3(0, 0, 0), 0, 0, 2));
	//RenderingEngine::getRenderingEngine()->addDirectionalLight(glm::fvec3(1, 0, 0), 1, glm::fvec3(1, 0, 0));

	//camera->setOrthographic(-5, 5, -5, 5, 0.1, 100);
}

void TestScene::gameInput(Display* display, float delta)
{
	//TEST CODE
	if (display->checkKey(SDLK_w))
	{
		glm::fvec3 movementAmount(camera->getForward().x * 0.1, camera->getForward().y * 0.1, camera->getForward().z * 0.1);
		camera->movePosition(movementAmount);
	}
	if (display->checkKey(SDLK_s))
	{
		glm::fvec3 movementAmount(camera->getForward().x * -0.1, camera->getForward().y * -0.1, camera->getForward().z * -0.1);
		camera->movePosition(movementAmount);
	}
	if (display->checkKey(SDLK_a))
	{
		glm::fvec3 movementAmount(camera->getLeft().x * 0.1, camera->getLeft().y * 0.1, camera->getLeft().z * 0.1);
		camera->movePosition(movementAmount);
	}
	if (display->checkKey(SDLK_d))
	{
		glm::fvec3 movementAmount(camera->getLeft().x * -0.1, camera->getLeft().y * -0.1, camera->getLeft().z * -0.1);
		camera->movePosition(movementAmount);
	}

	if (display->checkKey(SDLK_e))
	{
		root.getChild(0)->move(Vec9::createVec9(0.1, 0, 0, 0, 0, 0, 0, 0, 0));
	}
	if (display->checkKey(SDLK_r))
	{
		root.getChild(0)->move(Vec9::createVec9(-0.1, 0, 0, 0, 0, 0, 0, 0, 0));
	}
	if (display->checkKey(SDLK_t))
	{
		root.getChild(0)->getChild(0)->move(Vec9::createVec9(-0.1, 0, 0, 0, 0, 0, 0, 0, 0));
	}

	camera->rotateX(camera->getSensitivity() * display->getMouseDifX());
	camera->rotateY(camera->getSensitivity() * display->getMouseDifY());
}