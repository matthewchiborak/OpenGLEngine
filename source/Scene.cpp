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
void Scene::earlyUpdate()
{

}
void Scene::input(Display* display)
{
	
}
void Scene::lateUpdate()
{
	
}
//

void Scene::render()
{
	//Draw the objects
	//for (int i = 0; i < gameObjects.size(); i++)
	//{
	//	if (gameObjects.at(i)->isEnabled())
	//	{
	//		//Update speical updates on the objects
	//		gameObjects.at(i)->update();

	//		//gameObjects.at(i)->draw(camera);
	//		gameObjects.at(i)->render(camera);
	//	}
	//}
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

void Scene::update(Display* display)
{
	earlyUpdate();
	input(display);
	render();
	lateUpdate();
}