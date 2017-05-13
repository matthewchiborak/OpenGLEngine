#include "../include/Scene.h"

Scene::Scene(std::string name, float windowWidth, float windowHeight)
{
	this->name = name;
	//camera = new Camera(glm::vec3(0, 1, -5), 70.0f, (float)windowWidth / (float)windowWidth, 0.01f, 1000.0f);
	camera = new Camera(Vec9::createVec9(0, 1, -5, 0, 0, 1, 0, 1, 0), 70.0f, (float)windowWidth / (float)windowWidth, 0.01f, 1000.0f);

	level = NULL;
}

Scene::Scene(std::string name, std::string fileName, float windowWidth, float windowHeight)
{
	this->name = name;
	camera = new Camera(Vec9::createVec9(0, 1, -5, 0, 0, 1, 0, 1, 0), 70.0f, (float)windowWidth / (float)windowWidth, 0.01f, 1000.0f);

	//Read the bitmap and build the level around it
	generateLevel(fileName);
}

void Scene::generateLevel(std::string fileName)
{
	const float SPOT_WIDTH = 1;
	const float SPOT_HEIGHT = 1;
	const float SPOT_DEPTH = 1;
	static int NUM_TEX_EXP = 4;
	static int NUM_TEXTURES = pow(2, NUM_TEX_EXP);

	level = new Bitmap(".\\res\\Level1.png");
	level->flipX();
	level->flipY();

	for (int i = 0; i < level->getWidth(); i++)
	{
		for (int j = 0; j < level->getHeight(); j++)
		{
			if (level->getPixel(i, j).r == 0 && level->getPixel(i, j).g == 0 && level->getPixel(i, j).b == 0)
			{
				//Its a wall
				continue;
			}

			//Floor
			float XLow, XHigh, YLow, YHigh;
			level->calcTexCoords(level->getPixel(i, j).g, NUM_TEXTURES, NUM_TEX_EXP, &XLow, &XHigh, &YLow, &YHigh);

			addGameObjectToScene(GameObject::createSquarePartTexture(name + "_Floor_" + std::to_string(i) + "_" + std::to_string(j), SPOT_WIDTH, 0, SPOT_DEPTH, false, XLow, XHigh, YLow, YHigh, TextureManager::getTextureManager()->getTexture("Wolf"), ShaderManager::getShaderManager()->getShader("Phong")));
			getGameObject(name + "_Floor_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9(i * SPOT_WIDTH, 0, j * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));

			//Ceiling
			level->calcTexCoords(level->getPixel(i, j).r, NUM_TEXTURES, NUM_TEX_EXP, &XLow, &XHigh, &YLow, &YHigh);

			addGameObjectToScene(GameObject::createSquarePartTexture(name + "_Ceiling_" + std::to_string(i) + "_" + std::to_string(j), SPOT_WIDTH, 0, SPOT_DEPTH, true, XLow, XHigh, YLow, YHigh, TextureManager::getTextureManager()->getTexture("Wolf"), ShaderManager::getShaderManager()->getShader("Phong")));
			getGameObject(name + "_Ceiling_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9(i * SPOT_WIDTH, SPOT_HEIGHT, j * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));

			////walls. Check if ajacent is a wall
			level->calcTexCoords(level->getPixel(i, j).b, NUM_TEXTURES, NUM_TEX_EXP, &XLow, &XHigh, &YLow, &YHigh);

			if (level->getPixel(i, j - 1).r == 0 && level->getPixel(i, j - 1).g == 0 && level->getPixel(i, j - 1).b == 0)
			{
				addGameObjectToScene(GameObject::createCubePartTexture(name + "_Wall_a_" + std::to_string(i) + "_" + std::to_string(j), SPOT_WIDTH, SPOT_HEIGHT, 0, XLow, XHigh, YLow, YHigh, TextureManager::getTextureManager()->getTexture("Wolf"), ShaderManager::getShaderManager()->getShader("Phong")));
				getGameObject(name + "_Wall_a_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9(i * SPOT_WIDTH, SPOT_HEIGHT / 2, (j - 0.5) * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
			}
			if (level->getPixel(i, j + 1).r == 0 && level->getPixel(i, j + 1).g == 0 && level->getPixel(i, j + 1).b == 0)
			{
				addGameObjectToScene(GameObject::createCubePartTexture(name + "_Wall_b_" + std::to_string(i) + "_" + std::to_string(j), SPOT_WIDTH, SPOT_HEIGHT, 0, XLow, XHigh, YLow, YHigh, TextureManager::getTextureManager()->getTexture("Wolf"), ShaderManager::getShaderManager()->getShader("Phong")));
				getGameObject(name + "_Wall_b_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9(i * SPOT_WIDTH, SPOT_HEIGHT / 2, (j + 0.5) * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
			}
			if (level->getPixel(i - 1, j).r == 0 && level->getPixel(i - 1, j).g == 0 && level->getPixel(i - 1, j).b == 0)
			{
				addGameObjectToScene(GameObject::createCubePartTexture(name + "_Wall_c_" + std::to_string(i) + "_" + std::to_string(j), 0, SPOT_HEIGHT, SPOT_DEPTH, XLow, XHigh, YLow, YHigh, TextureManager::getTextureManager()->getTexture("Wolf"), ShaderManager::getShaderManager()->getShader("Phong")));
				getGameObject(name + "_Wall_c_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9((i - 0.5) * SPOT_WIDTH, SPOT_HEIGHT / 2, (j)* SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
			}
			if (level->getPixel(i + 1, j).r == 0 && level->getPixel(i + 1, j).g == 0 && level->getPixel(i + 1, j).b == 0)
			{
				addGameObjectToScene(GameObject::createCubePartTexture(name + "_Wall_d_" + std::to_string(i) + "_" + std::to_string(j), 0, SPOT_HEIGHT, SPOT_DEPTH, XLow, XHigh, YLow, YHigh, TextureManager::getTextureManager()->getTexture("Wolf"), ShaderManager::getShaderManager()->getShader("Phong")));
				getGameObject(name + "_Wall_d_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9((i + 0.5) * SPOT_WIDTH, SPOT_HEIGHT / 2, (j)* SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
			}
		}
	}
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

	if (level != NULL)
		delete level;
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