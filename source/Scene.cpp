#include "../include/Scene.h"

int Scene::NUM_TEX_EXP = 4;
int Scene::NUM_TEXTURES = pow(2, NUM_TEX_EXP);

Scene::Scene()
{
	lastTimeUpdated = Time::getTime();
}

Scene::Scene(std::string name, float windowWidth, float windowHeight)
{
	this->name = name;

	camera = new Camera(Vec9::createVec9(0, 1, -5, 0, 0, 1, 0, 1, 0), 70.0f, (float)windowWidth / (float)windowHeight, 0.01f, 1000.0f);

	lastTimeUpdated = Time::getTime();
}

Scene::Scene(std::string name, std::string fileName, float windowWidth, float windowHeight)
{
	this->name = name;
	camera = new Camera(Vec9::createVec9(0, 1, -5, 0, 0, 1, 0, 1, 0), 70.0f, (float)windowWidth / (float)windowHeight, 0.01f, 1000.0f);

	lastTimeUpdated = Time::getTime();
}

//More or less the base init function
void Scene::assignInfo(std::string name, int width, int height)
{
	this->name = name;

	camera = new Camera(Vec9::createVec9(0, 1, -5, 0, 0, 1, 0, 1, 0), 70.0f, (float)width / (float)height, 0.01f, 1000.0f);

	lastTimeUpdated = Time::getTime();
}

//MODIFIABLE
void Scene::init()
{
}



//

void Scene::moveCamera(Vec9 atLookUp)
{
	camera->movePosition(atLookUp.pos);
	camera->moveForward(atLookUp.rot);
	camera->moveUp(atLookUp.scale);
}
void Scene::resetCamera(Vec9 atLookUp)
{
	camera->setPosition(atLookUp.pos);
	camera->setForward(atLookUp.rot);
	camera->setUp(atLookUp.scale);
}

void Scene::setPerspective(float fov, float aspect, float zNear, float zFar)
{
	camera->setPerspective(fov, aspect, zNear, zFar);
}

void Scene::setNewCamera(Camera* camera)
{
	this->camera->setPosition(camera->getPosition());
	this->camera->setForward(camera->getForward());
	this->camera->setUp(camera->getUp());
	this->camera->setPerspective(camera->getPerspective());
}

Camera* Scene::getCamera()
{
	return camera;
}

Scene::~Scene()
{
	//Delete the game objects
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects.at(i) != NULL)
			delete gameObjects.at(i);
	}

	//TODO CLEAN UP THE SCENE GRAPH

	if (camera != NULL)
		delete camera;
}

std::string Scene::getName()
{
	return name;
}

void Scene::addGameObjectToScene(GameObject* object)
{
	gameObjects.push_back(object);
}

GameObject* Scene::getGameObject(std::string name)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects.at(i)->getName() == name)
		{
			return gameObjects.at(i);
		}
	}

	return NULL;
}

void Scene::update(float delta)
{
	root.update(delta);
}
void Scene::input(Display* display, float delta)
{
	root.input(delta);

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

//void Scene::baseUpdate()
//{
//	update();
//}
//
//void Scene::baseInput(Display* display)
//{
//	input(display);
//}
//void Scene::baseRender()
//{
//	render();
//}

GameObject* Scene::getRootObject()
{
	return &root;
}