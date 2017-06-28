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
	GameObject* testObject = new GameObject("Ship1");
	testObject->addComponent(testMR);
	testObject->setPhysicsObject(testPO);
	root.addChild(testObject);

	GameObject* testObject2 = new GameObject("Ship2");
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

	device = new SDLAudioDevice();

	//Create all the desired audio sources
	for (int i = 0; i < 3; i++)
	{
		audioSources.push_back(new SDLAudioContext());
	}

	//Test clip 1
	IAudioData* data = device->createAudioFromFile(".\\res\\testClip.wav");

	SampleInfo info;
	info.volume = 1.0;

	audioClips.push_back(new AudioObject(info, data));

	//Test Clip 2
	IAudioData* data2 = device->createAudioFromFile(".\\res\\starfox.wav");

	SampleInfo info2;
	info2.volume = 0.5;

	audioClips.push_back(new AudioObject(info2, data2));

	//TestClip 3
	IAudioData* data3 = device->createAudioFromFile(".\\res\\hit.wav");

	SampleInfo info3;
	info3.volume = 1.0;

	audioClips.push_back(new AudioObject(info3, data3));
}

void TestScene::gameInput(Display* display, float delta)
{
	//std::cout << objectsAffectedByPhysics.size() << "\n";

	//Check the physics events
	for (int i = 0; i < objectsAffectedByPhysics.size(); i++)
	{
		//Test sound effect
		if (objectsAffectedByPhysics.at(i)->getPhysicsObject()->getLastIntersetData().colliderName == "Ship1")
		{
			audioSources.at(2)->playAudio(*audioClips.at(2));
		}

		//Handle collisions
		glm::fvec3 direction = objectsAffectedByPhysics.at(i)->getPhysicsObject()->getLastIntersetData().getDirection() / objectsAffectedByPhysics.at(i)->getPhysicsObject()->getLastIntersetData().getDistance();
		//glm::fvec3 otherDirection = direction.Reflect(objects.at(i)->getVelocity().normalized);
		float directionMagnitude = sqrtf((objectsAffectedByPhysics.at(i)->getPhysicsObject()->getVelocity().x * objectsAffectedByPhysics.at(i)->getPhysicsObject()->getVelocity().x)
			+ (objectsAffectedByPhysics.at(i)->getPhysicsObject()->getVelocity().y * objectsAffectedByPhysics.at(i)->getPhysicsObject()->getVelocity().y)
			+ (objectsAffectedByPhysics.at(i)->getPhysicsObject()->getVelocity().z * objectsAffectedByPhysics.at(i)->getPhysicsObject()->getVelocity().z));

		glm::fvec3 tempDirection = objectsAffectedByPhysics.at(i)->getPhysicsObject()->getVelocity() / directionMagnitude;
		float reflect = 2 * ((direction.x * tempDirection.x) + (direction.y * tempDirection.y) + (direction.z * tempDirection.z));

		glm::fvec3 otherDirection = direction - (tempDirection * reflect);

		//Now to set the new velocities
		//glm::fvec3 newVelo1 = objects.at(i)->getVelocity().reflect(otherDirection);
		float reflect2 = 2 * ((objectsAffectedByPhysics.at(i)->getPhysicsObject()->getVelocity().x * otherDirection.x) + (objectsAffectedByPhysics.at(i)->getPhysicsObject()->getVelocity().y * otherDirection.y) + (objectsAffectedByPhysics.at(i)->getPhysicsObject()->getVelocity().z * otherDirection.z));
		glm::fvec3 newVelo1 = objectsAffectedByPhysics.at(i)->getPhysicsObject()->getVelocity() - (otherDirection * reflect2);
		objectsAffectedByPhysics.at(i)->getPhysicsObject()->setVelocity(newVelo1);

		//Test playing an audio clip on collision
		//audioSources.at(0)->playAudio(*audioClips.at(0));
	}

	//Handle Audio
	//audioSources.at(1)->playAudio(*audioClips.at(1));

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

	if (display->checkKey(SDLK_f))
	{
		audioSources.at(0)->playAudio(*audioClips.at(0));
	}
	if (display->checkKey(SDLK_r))
	{
		audioSources.at(0)->stopAudio(*audioClips.at(0));
	}
	if (display->checkKey(SDLK_t))
	{
		audioSources.at(0)->pauseAudio(*audioClips.at(0));
	}

	//Test looping background music
	audioSources.at(1)->playAudio(*audioClips.at(1));

	//if (display->checkKey(SDLK_e))
	//{
	//	//root.getChild(0)->move(Vec9::createVec9(0.1, 0, 0, 0, 0, 0, 0, 0, 0));
	//	AudioSource testSource;
	//	testSource.setAudioClip(AudioEngine::getAudioEngine()->getAudioClip("SCM"));
	//	testSource.play();
	//}
	//if (display->checkKey(SDLK_r))
	//{
	//	root.getChild(0)->move(Vec9::createVec9(-0.1, 0, 0, 0, 0, 0, 0, 0, 0));
	//}
	//if (display->checkKey(SDLK_t))
	//{
	//	root.getChild(0)->getChild(0)->move(Vec9::createVec9(-0.1, 0, 0, 0, 0, 0, 0, 0, 0));
	//}

	camera->rotateX(camera->getSensitivity() * display->getMouseDifX());
	camera->rotateY(camera->getSensitivity() * display->getMouseDifY());
}