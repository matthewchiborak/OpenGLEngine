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
	PhysicsObject* testPO = new PhysicsObject(new BoundingSphere(glm::fvec3(0, 0, 0), 1), glm::fvec3(0, 0, 1));
	GameObject* testObject = new GameObject();
	testObject->addComponent(testMR);
	testObject->setPhysicsObject(testPO);
	root.addChild(testObject);

	GameObject* testObject2 = new GameObject();
	//MeshRenderer* testMR2 = new MeshRenderer(MeshManager::getMeshManager()->getMesh("Arwing"), TextureManager::getTextureManager()->getTexture("Arwing"), ShaderManager::getShaderManager()->getShader("Phong"));
	MeshRenderer* testMR2 = new MeshRenderer(MeshManager::getMeshManager()->getMesh("Arwing"), TextureManager::getTextureManager()->getTexture("Arwing"));
	PhysicsObject* testPO2 = new PhysicsObject(new BoundingSphere(glm::fvec3(0, 0, 0), 1), glm::fvec3(0, 0, -1.5));
	testObject2->addComponent(testMR2);
	testObject2->setPhysicsObject(testPO2);
	//testObject->addChild(testObject2);
	root.addChild(testObject2);
	testObject2->move(Vec9::createVec9(0.5, 0, 20, 0, 0, 0, 0, 0, 0));

	//Render 
	//testObject->addDirectionalLight(new DirectionalLight(glm::fvec3(1, 0, 0), glm::fvec3(1, 0, 0), 1));
	testObject2->addPointLight(new PointLight(glm::fvec3(0, 1, 0), 10, glm::fvec3(0, 0, 0), 0, 0, 2));
	//RenderingEngine::getRenderingEngine()->addDirectionalLight(glm::fvec3(1, 0, 0), 1, glm::fvec3(1, 0, 0));

	//camera->setOrthographic(-5, 5, -5, 5, 0.1, 100);

	//Physics Test Setup
	//PhysicsEngine::getPhysicsEngine()->addObject(new PhysicsObject(new BoundingSphere(glm::fvec3(0.5, 0, 0), 1), glm::fvec3(0, 0, 1)));
	//PhysicsEngine::getPhysicsEngine()->addObject(new PhysicsObject(new BoundingSphere(glm::fvec3(0, 0, 10), 1), glm::fvec3(0, 0, -1.5)));
}

void TestScene::gameInput(Display* display, float delta)
{
	//std::cout << objectsAffectedByPhysics.size() << "\n";

	//Check the physics events
	for (int i = 0; i < objectsAffectedByPhysics.size(); i++)
	{
		std::cout << i << ": ObjectPos: " << objectsAffectedByPhysics.at(i)->getTransform()->GetPos().z << "\n";
		std::cout << i << ": PhysicsObjectPos: " << objectsAffectedByPhysics.at(i)->getPhysicsObject()->getPosition().z << "\n";
		std::cout << i << ": PhysicsObjectPos: " << objectsAffectedByPhysics.at(i)->getPhysicsObject()->getVelocity().z << "\n";
		std::cout << i << ": ColliderCenter: " << objectsAffectedByPhysics.at(i)->getPhysicsObject()->getCollider()->getCenter().z << "\n";
	}

	//TEST CODE
	if (display->checkKey(SDLK_w))
	{
		glm::fvec3 movementAmount(camera->getForward().x * 0.1,0, camera->getForward().z * 0.1);
		camera->movePosition(movementAmount);
	}
	if (display->checkKey(SDLK_s))
	{
		glm::fvec3 movementAmount(camera->getForward().x * -0.1, 0, camera->getForward().z * -0.1);
		camera->movePosition(movementAmount);
	}
	if (display->checkKey(SDLK_a))
	{
		glm::fvec3 movementAmount(camera->getLeft().x * 0.1, 0, camera->getLeft().z * 0.1);
		camera->movePosition(movementAmount);
	}
	if (display->checkKey(SDLK_d))
	{
		glm::fvec3 movementAmount(camera->getLeft().x * -0.1, 0, camera->getLeft().z * -0.1);
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