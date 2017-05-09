#include "../include/Scene.h"

Scene::Scene(std::string name, float windowWidth, float windowHeight)
{
	this->name = name;
	//camera = new Camera(glm::vec3(0, 1, -5), 70.0f, (float)windowWidth / (float)windowWidth, 0.01f, 1000.0f);
	camera = new Camera(Vec9::createVec9(0, 1, -5, 0, 0, 1, 0, 1, 0), 70.0f, (float)windowWidth / (float)windowWidth, 0.01f, 1000.0f);
}

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
	for (int i = 0; i < inputs.size(); i++)
	{
		if(inputs.at(i) != NULL)
			delete inputs.at(i);
	}
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if(gameObjects.at(i) != NULL)
			delete gameObjects.at(i);
	}
		
	if(camera != NULL)
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

void Scene::addInputToScene(Input* input)
{
	inputs.push_back(input);
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

void Scene::update(Display* display)
{
	//Check player input
	for (int i = 0; i < inputs.size(); i++)
	{
		inputs.at(i)->execute(display);
	}

	//Draw the objects
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects.at(i)->draw(camera);
	}
}