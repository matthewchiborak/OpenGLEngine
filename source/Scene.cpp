#include "../include/Scene.h"

float Scene::PLAYER_SIZE = 0.3f;
int Scene::NUM_TEX_EXP = 4;
int Scene::NUM_TEXTURES = pow(2, NUM_TEX_EXP);

Scene::Scene(std::string name, float windowWidth, float windowHeight)
{
	this->name = name;
	//camera = new Camera(glm::vec3(0, 1, -5), 70.0f, (float)windowWidth / (float)windowWidth, 0.01f, 1000.0f);
	camera = new Camera(Vec9::createVec9(0, 1, -5, 0, 0, 1, 0, 1, 0), 70.0f, (float)windowWidth / (float)windowWidth, 0.01f, 1000.0f);

	level = NULL;
	lastTimeUpdated = Time::getTime();
}

Scene::Scene(std::string name, std::string fileName, float windowWidth, float windowHeight)
{
	this->name = name;
	camera = new Camera(Vec9::createVec9(0, 1, -5, 0, 0, 1, 0, 1, 0), 70.0f, (float)windowWidth / (float)windowWidth, 0.01f, 1000.0f);

	//Read the bitmap and build the level around it
	generateLevel(fileName);

	lastTimeUpdated = Time::getTime();
}

void Scene::generateLevel(std::string fileName)
{
	level = new Bitmap(".\\res\\Level1.png");
	level->flipX();
	level->flipY();

	//TEST
	float XLow, XHigh, YLow, YHigh;
	//level->calcTexCoords(79, NUM_TEXTURES, NUM_TEX_EXP, &XLow, &XHigh, &YLow, &YHigh);
	Monster* tempDoor = new Monster("TestMob", Monster::SIZEX, Monster::SIZEY, 0, 0, 1, 0, 1, TextureManager::getTextureManager()->getTexture("SSWVA1"), ShaderManager::getShaderManager()->getShader("Phong"), camera, this);
	addGameObjectToScene(tempDoor);
	getGameObject("TestMob")->setTransform(Vec9::createVec9(17 * SPOT_WIDTH, 0.5 * SPOT_HEIGHT - 0.25 * Monster::SIZEY, 19 * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
	//TEST

	for (int i = 0; i < level->getWidth(); i++)
	{
		for (int j = 0; j < level->getHeight(); j++)
		{
			if (level->getPixel(i, j).r == 0 && level->getPixel(i, j).g == 0 && level->getPixel(i, j).b == 0)
			{
				//Its a wall
				continue;
			}

			//Add special components like the doors
			addSpecial(level->getPixel(i, j).b, i, j);

			//Floor
			/*float XLow, XHigh, YLow, YHigh;*/
			level->calcTexCoords(level->getPixel(i, j).g, NUM_TEXTURES, NUM_TEX_EXP, &XLow, &XHigh, &YLow, &YHigh);

			addGameObjectToScene(GameObject::createSquarePartTexture(name + "_Floor_" + std::to_string(i) + "_" + std::to_string(j), SPOT_WIDTH, 0, SPOT_DEPTH, false, XLow, XHigh, YLow, YHigh, TextureManager::getTextureManager()->getTexture("Wolf"), ShaderManager::getShaderManager()->getShader("Phong")));
			getGameObject(name + "_Floor_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9(i * SPOT_WIDTH, 0, j * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));

			//Ceiling
			level->calcTexCoords(level->getPixel(i, j).r, NUM_TEXTURES, NUM_TEX_EXP, &XLow, &XHigh, &YLow, &YHigh);

			addGameObjectToScene(GameObject::createSquarePartTexture(name + "_Ceiling_" + std::to_string(i) + "_" + std::to_string(j), SPOT_WIDTH, 0, SPOT_DEPTH, true, XLow, XHigh, YLow, YHigh, TextureManager::getTextureManager()->getTexture("Wolf"), ShaderManager::getShaderManager()->getShader("Phong")));
			getGameObject(name + "_Ceiling_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9(i * SPOT_WIDTH, SPOT_HEIGHT, j * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));

			////walls. Check if ajacent is a wall
			level->calcTexCoords(level->getPixel(i, j).r, NUM_TEXTURES, NUM_TEX_EXP, &XLow, &XHigh, &YLow, &YHigh);

			if (level->getPixel(i, j - 1).r == 0 && level->getPixel(i, j - 1).g == 0 && level->getPixel(i, j - 1).b == 0)
			{
				collisionPosStart.push_back(new glm::fvec2(i * SPOT_WIDTH, j * SPOT_DEPTH));
				collisionPosEnd.push_back(new glm::fvec2((i + 1) * SPOT_WIDTH, j * SPOT_DEPTH));

				addGameObjectToScene(GameObject::createCubePartTexture(name + "_Wall_a_" + std::to_string(i) + "_" + std::to_string(j), SPOT_WIDTH, SPOT_HEIGHT, 0, XLow, XHigh, YLow, YHigh, TextureManager::getTextureManager()->getTexture("Wolf"), ShaderManager::getShaderManager()->getShader("Phong")));
				getGameObject(name + "_Wall_a_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9(i * SPOT_WIDTH, SPOT_HEIGHT / 2, (j - 0.5) * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
			}
			if (level->getPixel(i, j + 1).r == 0 && level->getPixel(i, j + 1).g == 0 && level->getPixel(i, j + 1).b == 0)
			{
				collisionPosStart.push_back(new glm::fvec2(i * SPOT_WIDTH, (j + 1) * SPOT_DEPTH));
				collisionPosEnd.push_back(new glm::fvec2((i + 1) * SPOT_WIDTH, (j + 1) * SPOT_DEPTH));

				addGameObjectToScene(GameObject::createCubePartTexture(name + "_Wall_b_" + std::to_string(i) + "_" + std::to_string(j), SPOT_WIDTH, SPOT_HEIGHT, 0, XLow, XHigh, YLow, YHigh, TextureManager::getTextureManager()->getTexture("Wolf"), ShaderManager::getShaderManager()->getShader("Phong")));
				getGameObject(name + "_Wall_b_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9(i * SPOT_WIDTH, SPOT_HEIGHT / 2, (j + 0.5) * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
			}
			if (level->getPixel(i - 1, j).r == 0 && level->getPixel(i - 1, j).g == 0 && level->getPixel(i - 1, j).b == 0)
			{
				collisionPosStart.push_back(new glm::fvec2(i * SPOT_WIDTH, (j) * SPOT_DEPTH));
				collisionPosEnd.push_back(new glm::fvec2((i) * SPOT_WIDTH, (j + 1) * SPOT_DEPTH));

				addGameObjectToScene(GameObject::createCubePartTexture(name + "_Wall_c_" + std::to_string(i) + "_" + std::to_string(j), 0, SPOT_HEIGHT, SPOT_DEPTH, XLow, XHigh, YLow, YHigh, TextureManager::getTextureManager()->getTexture("Wolf"), ShaderManager::getShaderManager()->getShader("Phong")));
				getGameObject(name + "_Wall_c_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9((i - 0.5) * SPOT_WIDTH, SPOT_HEIGHT / 2, (j)* SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
			}
			if (level->getPixel(i + 1, j).r == 0 && level->getPixel(i + 1, j).g == 0 && level->getPixel(i + 1, j).b == 0)
			{
				collisionPosStart.push_back(new glm::fvec2((i + 1) * SPOT_WIDTH, (j) * SPOT_DEPTH));
				collisionPosEnd.push_back(new glm::fvec2((i + 1) * SPOT_WIDTH, (j + 1) * SPOT_DEPTH));

				addGameObjectToScene(GameObject::createCubePartTexture(name + "_Wall_d_" + std::to_string(i) + "_" + std::to_string(j), 0, SPOT_HEIGHT, SPOT_DEPTH, XLow, XHigh, YLow, YHigh, TextureManager::getTextureManager()->getTexture("Wolf"), ShaderManager::getShaderManager()->getShader("Phong")));
				getGameObject(name + "_Wall_d_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9((i + 0.5) * SPOT_WIDTH, SPOT_HEIGHT / 2, (j)* SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
			}
		}
	}
}

void Scene::addSpecial(int blueValue, int x, int z)
{
	if (blueValue == 16)
	{
		float XLow, XHigh, YLow, YHigh;
		level->calcTexCoords(79, NUM_TEXTURES, NUM_TEX_EXP, &XLow, &XHigh, &YLow, &YHigh);
		Door* tempDoor;
		
		if ((level->getPixel(x + 1, z).r == 0 && level->getPixel(x + 1, z).g == 0 && level->getPixel(x + 1, z).b == 0) && (level->getPixel(x - 1, z).r == 0 && level->getPixel(x - 1, z).g == 0 && level->getPixel(x - 1, z).b == 0))
		{
			tempDoor = new Door("TestDoor_" + std::to_string(x) + "_" + std::to_string(z), SPOT_WIDTH, SPOT_HEIGHT, DOOR_THICKNESS, XLow, XHigh, YLow, YHigh, TextureManager::getTextureManager()->getTexture("Wolf"), ShaderManager::getShaderManager()->getShader("Phong"));
		}
		else if ((level->getPixel(x, z + 1).r == 0 && level->getPixel(x, z + 1).g == 0 && level->getPixel(x, z + 1).b == 0) && (level->getPixel(x, z - 1).r == 0 && level->getPixel(x, z - 1).g == 0 && level->getPixel(x, z - 1).b == 0))
		{
			tempDoor = new Door("TestDoor_" + std::to_string(x) + "_" + std::to_string(z), DOOR_THICKNESS, SPOT_HEIGHT, SPOT_DEPTH, XLow, XHigh, YLow, YHigh, TextureManager::getTextureManager()->getTexture("Wolf"), ShaderManager::getShaderManager()->getShader("Phong"));
		}
		else
		{
			std::cerr << "Failed to create door. Invalid location: " << x << " " << z << "\n";
			return;
		}

		addGameObjectToScene(tempDoor);
		doors.push_back(tempDoor);
		getGameObject("TestDoor_" + std::to_string(x) + "_" + std::to_string(z))->setTransform(Vec9::createVec9(x * SPOT_WIDTH, 0.5 * SPOT_HEIGHT, z * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
		getGameObject("TestDoor_" + std::to_string(x) + "_" + std::to_string(z))->init();
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

	for (int i = 0; i < collisionPosStart.size(); i++)
	{
		if (collisionPosStart.at(i) != NULL)
			delete collisionPosStart.at(i);
	}
	for (int i = 0; i < collisionPosEnd.size(); i++)
	{
		if (collisionPosEnd.at(i) != NULL)
			delete collisionPosEnd.at(i);
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
	input->assignScene(this);
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
		//Update speical updates on the objects
		gameObjects.at(i)->update();

		gameObjects.at(i)->draw(camera);
	}
}

glm::fvec3 Scene::checkCollisionCameraWalls(Camera* camera, glm::fvec3 movement, float objectWidth, float objectHeight, float objectDepth)
{
	//If a collision, change the result to 0;
	glm::fvec3 collisionVector(1, 1, 1);

	float offsetX = 0.5 * SPOT_WIDTH;
	float offsetZ = 0.5 * SPOT_DEPTH;

	if (movement.x < 0)
	{
		offsetX = 0;
	}
	if (movement.z < 0)
	{
		offsetZ = 0;
	}

	//Find the grid square the camera is trying to move into
	int camInX = (camera->getPosition().x) / (SPOT_WIDTH) + 0.5 * SPOT_WIDTH;
	int camInZ = (camera->getPosition().z) / (SPOT_DEPTH) + 0.5 * SPOT_DEPTH;
	int camWantGoX = (camera->getPosition().x + movement.x + offsetX) / (SPOT_WIDTH) + 0.5 * SPOT_WIDTH;
	int camWantGoZ = (camera->getPosition().z + movement.z + offsetZ) / (SPOT_DEPTH) + 0.5 * SPOT_DEPTH;

	if (movement.x != 0)
	{
		if (level->getPixel(camWantGoX, camInZ).r == 0 && level->getPixel(camWantGoX, camInZ).g == 0 && level->getPixel(camWantGoX, camInZ).b == 0)
		{
			collisionVector.x = 0;
		}
	}
	/*if (movement.y > 0)
	{

	}*/
	if (movement.z != 0)
	{
		if (level->getPixel(camInX, camWantGoZ).r == 0 && level->getPixel(camInX, camWantGoZ).g == 0 && level->getPixel(camInX, camWantGoZ).b == 0)
		{
			collisionVector.z = 0;
		}
	}

	//Check if collide with door
	for (int i = 0; i < doors.size(); i++)
	{
		if (doors.at(i)->getTransform()->GetPos().x / (SPOT_WIDTH) == camWantGoX && doors.at(i)->getTransform()->GetPos().z / (SPOT_DEPTH) == camInZ)
		{
			collisionVector.x = 0;
		}
		if (doors.at(i)->getTransform()->GetPos().z / (SPOT_DEPTH) == camWantGoZ && doors.at(i)->getTransform()->GetPos().x / (SPOT_WIDTH) == camInX)
		{
			collisionVector.z = 0;
		}
	}

	return collisionVector;
}

glm::fvec3 Scene::checkCollisionEnemyWalls(Monster* monster, glm::fvec3 movement, float objectWidth, float objectHeight, float objectDepth)
{
	//If a collision, change the result to 0;
	glm::fvec3 collisionVector(1, 1, 1);

	float offsetX = 0.5 * SPOT_WIDTH;
	float offsetZ = 0.5 * SPOT_DEPTH;

	if (movement.x < 0)
	{
		offsetX = 0;
	}
	if (movement.z < 0)
	{
		offsetZ = 0;
	}

	//Find the grid square the camera is trying to move into
	int camInX = (monster->getTransform()->GetPos().x) / (SPOT_WIDTH)+0.5 * SPOT_WIDTH;
	int camInZ = (monster->getTransform()->GetPos().z) / (SPOT_DEPTH)+0.5 * SPOT_DEPTH;
	int camWantGoX = (monster->getTransform()->GetPos().x + movement.x + offsetX) / (SPOT_WIDTH)+0.5 * SPOT_WIDTH;
	int camWantGoZ = (monster->getTransform()->GetPos().z + movement.z + offsetZ) / (SPOT_DEPTH)+0.5 * SPOT_DEPTH;

	if (movement.x != 0)
	{
		if (level->getPixel(camWantGoX, camInZ).r == 0 && level->getPixel(camWantGoX, camInZ).g == 0 && level->getPixel(camWantGoX, camInZ).b == 0)
		{
			collisionVector.x = 0;
		}
	}
	/*if (movement.y > 0)
	{

	}*/
	if (movement.z != 0)
	{
		if (level->getPixel(camInX, camWantGoZ).r == 0 && level->getPixel(camInX, camWantGoZ).g == 0 && level->getPixel(camInX, camWantGoZ).b == 0)
		{
			collisionVector.z = 0;
		}
	}

	//Check if collide with door
	for (int i = 0; i < doors.size(); i++)
	{
		if (doors.at(i)->getTransform()->GetPos().x / (SPOT_WIDTH) == camWantGoX && doors.at(i)->getTransform()->GetPos().z / (SPOT_DEPTH) == camInZ)
		{
			doors.at(i)->open();
			collisionVector.x = 0;
		}
		if (doors.at(i)->getTransform()->GetPos().z / (SPOT_DEPTH) == camWantGoZ && doors.at(i)->getTransform()->GetPos().x / (SPOT_WIDTH) == camInX)
		{
			doors.at(i)->open();
			collisionVector.z = 0;
		}
	}

	return collisionVector;
}

glm::fvec3 Scene::checkCollisionCamera(Camera* camera, glm::fvec3 movement, float objectWidth, float objectHeight, float objectDepth)
{
	//If a collision, change the result to 0;
	glm::fvec3 collisionVector(1, 1, 1);

	if (movement.x != 0 || movement.y != 0 || movement.z != 0)
	{
		glm::fvec3 blockSize(SPOT_WIDTH, SPOT_HEIGHT, SPOT_DEPTH);
		glm::fvec3 objectSize(objectWidth, objectHeight, objectDepth);
		glm::fvec3 oldPos2(camera->getPosition());
		glm::fvec3 newPos2(camera->getPosition() + movement);

		int width = level->getWidth();
		int depth = level->getHeight();

		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < depth; j++)
			{
				if (level->getPixel(i,j).r == 0 && level->getPixel(i, j).g == 0 && level->getPixel(i, j).b == 0)
				{
					collisionVector *= rectCollide(oldPos2, newPos2, objectSize, blockSize, blockSize * glm::fvec3(i, 0, j));
				}
			}
		}
	}

	return collisionVector;
}

glm::fvec3 Scene::rectCollide(glm::fvec3 oldPos, glm::fvec3 newPos, glm::fvec3 size1, glm::fvec3 size2, glm::fvec3 pos2)
{
	glm::fvec3 result(0, 0, 0);

	if (newPos.x + size1.x + (size1.x / 2) < pos2.x ||
		newPos.x - size1.x + (size1.x / 2) > pos2.x + size2.x * size2.x ||
		oldPos.z + size1.z + (size1.x / 2) < pos2.z ||
		oldPos.z - size1.z + (size1.x / 2) > pos2.z + size2.z * size2.z)
	{
		result.x = 1;
	}

	if (oldPos.x + size1.x + (size1.x/2) < pos2.x ||
		oldPos.x - size1.x + (size1.x / 2) > pos2.x + size2.x * size2.x ||
		newPos.z + size1.z + (size1.x / 2) < pos2.z ||
		newPos.z - size1.z + (size1.x / 2) > pos2.z + size2.z * size2.z)
	{
		result.z = 1;
	}

	return result;
}

std::vector<Door*>* Scene::getDoors()
{
	return &doors;
}

glm::fvec2 Scene::checkIntersection(glm::fvec2 lineStart, glm::fvec2 lineEnd)
{
	//Find nearest intersection to the start of the line
	glm::fvec2 nearestInterestion(0, 0);
	bool foundOne = false;

	for (int i = 0; i < collisionPosStart.size(); i++)
	{
		glm::fvec2 collisionVector = lineIntersect(lineStart, lineEnd, *collisionPosStart.at(i), *collisionPosEnd.at(i));

		if ((!foundOne || (getLineLength(nearestInterestion - lineStart) > getLineLength(collisionVector - lineStart))) 
			&& collisionVector.x != 0 && collisionVector.y != 0)
		{
			foundOne = true;
			nearestInterestion = collisionVector;
		}
	}

	for (int i = 0; i < doors.size(); i ++)
	{
		glm::fvec2 doorSize(SPOT_WIDTH, SPOT_DEPTH);
		glm::fvec2 doorPos2f(doors.at(i)->getDimensions().x, doors.at(i)->getDimensions().z);
		
		glm::fvec2 collisionVector = lineInterestRect(lineStart, lineEnd, doorPos2f, doorSize);

		nearestInterestion = findNearestVector2(nearestInterestion, collisionVector, lineStart);
	}

	return nearestInterestion;
}

float Scene::getLineLength(glm::fvec2 line)
{
	return sqrtf(line.x * line.x + line.y * line.y);
}

float Scene::crossProduct(glm::fvec2 a, glm::fvec2 b)
{
	return a.x * b.y - a.y * b.x;
}

glm::fvec2 Scene::lineIntersect(glm::fvec2 lineStart1, glm::fvec2 lineEnd1, glm::fvec2 lineStart2, glm::fvec2 lineEnd2)
{
	glm::fvec2 result(0, 0);
	glm::fvec2 line1 = lineEnd1 - lineStart1;
	glm::fvec2 line2 = lineEnd2 - lineStart2;

	//lineStart1 + line1 * a == lineStart2 + line2 * b. If so, they intersect

	float cross = crossProduct(line1, line2);

	//Parallel
	if (cross == 0)
	{
		return result;
	}

	glm::fvec2 distanceBetweenStarts = lineStart2 - lineStart1;

	float a = crossProduct(distanceBetweenStarts, line2) / cross;
	float b = crossProduct(distanceBetweenStarts, line1) / cross;

	if (-0.01 < a && a < 1 && -0.01 < b && b < 1)
	{
		//Within range
		result.x = line1.x + line1.x * a;
		result.y = line1.y + line1.y * a;
	}

	return result;
}

glm::fvec2 Scene::lineInterestRect(glm::fvec2 lineStart, glm::fvec2 lineEnd)
{
	glm::fvec2 pos(camera->getPosition().x, camera->getPosition().z);
	glm::fvec2 size(PLAYER_SIZE, PLAYER_SIZE);
	glm::fvec2 posSize(pos.x + size.x, pos.y);
	glm::fvec2 posSize2;

	glm::fvec2 result(0, 0);

	//Side 1
	glm::fvec2 collisionVector = lineIntersect(lineStart, lineEnd, pos, posSize);
	result = findNearestVector2(result, collisionVector, lineStart);

	//2
	posSize.x = pos.x;
	posSize.y = pos.y + size.y;
	collisionVector = lineIntersect(lineStart, lineEnd, pos, posSize);
	result = findNearestVector2(result, collisionVector, lineStart);

	//3
	posSize2.x = pos.x;
	posSize2.y = pos.y + size.y;
	posSize.x = pos.x + size.x;
	posSize.y = pos.y + size.y;
	collisionVector = lineIntersect(lineStart, lineEnd, posSize2, posSize);
	result = findNearestVector2(result, collisionVector, lineStart);

	//4
	posSize2.x = pos.x + size.x;
	posSize2.y = pos.y;
	collisionVector = lineIntersect(lineStart, lineEnd, posSize2, posSize);
	result = findNearestVector2(result, collisionVector, lineStart);

	return result;
}

glm::fvec2 Scene::lineInterestRect(glm::fvec2 lineStart, glm::fvec2 lineEnd, glm::fvec2 pos, glm::fvec2 size)
{
	glm::fvec2 posSize(pos.x + size.x, pos.y);
	glm::fvec2 posSize2;

	glm::fvec2 result(0, 0);

	//Side 1
	glm::fvec2 collisionVector = lineIntersect(lineStart, lineEnd, pos, posSize);
	result = findNearestVector2(result, collisionVector, lineStart);

	//2
	posSize.x = pos.x;
	posSize.y = pos.y + size.y;
	collisionVector = lineIntersect(lineStart, lineEnd, pos, posSize);
	result = findNearestVector2(result, collisionVector, lineStart);

	//3
	posSize2.x = pos.x;
	posSize2.y = pos.y + size.y;
	posSize.x = pos.x + size.x;
	posSize.y = pos.y + size.y;
	collisionVector = lineIntersect(lineStart, lineEnd, posSize2, posSize);
	result = findNearestVector2(result, collisionVector, lineStart);

	//4
	posSize2.x = pos.x + size.x;
	posSize2.y = pos.y;
	collisionVector = lineIntersect(lineStart, lineEnd, posSize2, posSize);
	result = findNearestVector2(result, collisionVector, lineStart);

	return result;
}

glm::fvec2 Scene::findNearestVector2(glm::fvec2 a, glm::fvec2 b, glm::fvec2 positionRelativeTo)
{
	/*if (((getLineLength(a - positionRelativeTo) > getLineLength(a - positionRelativeTo)))
		&& b.x != 0 && b.y != 0)
	{
		return a;
	}*/
	if ((b.x != 0 && b.y != 0) && ((a.x == 0 && a.y == 0) ||
		(getLineLength(a - positionRelativeTo) > getLineLength(b - positionRelativeTo))))
	{
		return b;
	}

	return a;
}