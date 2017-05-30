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
	Mesh* testMesh = new Mesh(".\\res\\arwing.obj");
	MeshRenderer* testMR = new MeshRenderer(testMesh, TextureManager::getTextureManager()->getTexture("Arwing"), ShaderManager::getShaderManager()->getShader("Phong"));
	//root.addComponent(testMR);
	GameObject* testObject = new GameObject();
	testObject->addComponent(testMR);
	root.addChild(testObject);

	GameObject* testObject2 = new GameObject();
	MeshRenderer* testMR2 = new MeshRenderer(testMesh, TextureManager::getTextureManager()->getTexture("Arwing"), ShaderManager::getShaderManager()->getShader("Phong"));
	testObject2->addComponent(testMR2);
	testObject->addChild(testObject2);
	testObject2->move(Vec9::createVec9(1, 0, 0, 0, 0, 0, 0, 0, 0));

	//Render 
	testObject->addDirectionalLight(new DirectionalLight(glm::fvec3(1, 0, 0), glm::fvec3(1, 0, 0), 1));
	//RenderingEngine::getRenderingEngine()->addDirectionalLight(glm::fvec3(1, 0, 0), 1, glm::fvec3(1, 0, 0));

	//camera->setOrthographic(-5, 5, -5, 5, 0.1, 100);
}

//void TestScene::render()
//{
//	root.render(camera);
//}
//
//void TestScene::update()
//{
//	root.update();
//}
//
//void TestScene::input(Display* display)
//{
//	//TODO camera input
//
//	root.input();
//
//	if (display->checkKey(SDLK_f))
//	{
//		//getGameObject("Ship")->getTransform()->GetRot().y += 0.1;
//	}
//	if (display->checkKey(SDLK_w))
//	{
//		glm::fvec3 movementAmount(camera->getForward().x * 0.1, camera->getForward().y * 0.1, camera->getForward().z * 0.1);
//		camera->movePosition(movementAmount);
//	}
//	if (display->checkKey(SDLK_s))
//	{
//		glm::fvec3 movementAmount(camera->getForward().x * -0.1, camera->getForward().y * -0.1, camera->getForward().z * -0.1);
//		camera->movePosition(movementAmount);
//	}
//	if (display->checkKey(SDLK_a))
//	{
//		glm::fvec3 movementAmount(camera->getLeft().x * 0.1, camera->getLeft().y * 0.1, camera->getLeft().z * 0.1);
//		camera->movePosition(movementAmount);
//	}
//	if (display->checkKey(SDLK_d))
//	{
//		glm::fvec3 movementAmount(camera->getLeft().x * -0.1, camera->getLeft().y * -0.1, camera->getLeft().z * -0.1);
//		camera->movePosition(movementAmount);
//	}
//
//	camera->rotateY(camera->getSensitivity() * display->getMouseDifX());
//}