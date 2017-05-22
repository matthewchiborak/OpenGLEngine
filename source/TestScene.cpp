#include "../include/TestScene.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
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
	for (int i = 0; i < exits.size(); i++)
	{
		if (exits.at(i) != NULL)
		{
			delete exits.at(i);
		}
	}

	if (level != NULL)
		delete level;
}

void TestScene::update()
{

}

void TestScene::lateUpdate()
{
	//HUD Update. TODO make a class to handle this
	//Have the HUD always face the player
	glm::fvec3 directToCam = HUD->getTransform()->GetPos() - camera->getPosition();

	float angleToFaceCam = atan((directToCam.z / directToCam.x));

	if (directToCam.x > 0)
	{
		angleToFaceCam += 3.1415;
	}

	HUD->getTransform()->SetRot(glm::fvec3(0, (angleToFaceCam + (3.1415 / 2)) * -1, 0));

	HUD->getTransform()->GetPos().x = camera->getPosition().x + camera->getForward().x;// * 1.25;// * 0.25;
																					   //HUD->getTransform()->GetPos().y = camera->getPosition().y;
	HUD->getTransform()->GetPos().z = camera->getPosition().z + camera->getForward().z; //*1.25; //* 0.25;

	HUD->draw(camera);
}

void TestScene::init()
{
	generateLevel(fileName);

	/*addInputToScene(new Input(KEY_PRESS_FORWARD_CAMERA_TRANSFORM, getCamera(), SDLK_w, 0.1));
	addInputToScene(new Input(KEY_PRESS_FORWARD_CAMERA_TRANSFORM, getCamera(), SDLK_s, -0.1));
	addInputToScene(new Input(KEY_PRESS_LEFT_CAMERA_TRANSFORM, getCamera(), SDLK_d, 0.1));
	addInputToScene(new Input(KEY_PRESS_LEFT_CAMERA_TRANSFORM, getCamera(), SDLK_a, -0.1));
	addInputToScene(new Input(MOUSE_MOVE_X_TRANSFORM, getCamera()));

	addInputToScene(new Input(KEY_PRESS_DOWN_DOOR_OPEN, getCamera(), SDLK_f, getDoors()));
	addInputToScene(new Input(LEFT_CLICK_DOWN_SHOOT, getCamera(), getMonsters()));*/
}

void TestScene::input(Display* display)
{
	if (display->checkKey(SDLK_w))
	{
		glm::fvec3 movementAmount(camera->getForward().x * 0.1, camera->getForward().y * 0.1, camera->getForward().z * 0.1);
		glm::fvec3 collisionResult = checkCollisionCameraWalls(camera, movementAmount, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE);

		movementAmount.x *= collisionResult.x;
		movementAmount.y *= collisionResult.y;
		movementAmount.z *= collisionResult.z;

		camera->movePosition(movementAmount);
	}
	if (display->checkKey(SDLK_s))
	{
		glm::fvec3 movementAmount(camera->getForward().x * -0.1, camera->getForward().y * -0.1, camera->getForward().z * -0.1);
		glm::fvec3 collisionResult = checkCollisionCameraWalls(camera, movementAmount, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE);

		movementAmount.x *= collisionResult.x;
		movementAmount.y *= collisionResult.y;
		movementAmount.z *= collisionResult.z;

		camera->movePosition(movementAmount);
	}
	if (display->checkKey(SDLK_d))
	{
		glm::vec3 left = glm::cross(camera->getForward(), camera->getUp());

		glm::fvec3 movementAmount(left.x * 0.1, left.y * 0.1, left.z * 0.1);

		//glm::fvec3 collisionResult = myScene->checkCollisionCamera(cameraObject, movementAmount, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE);
		glm::fvec3 collisionResult = checkCollisionCameraWalls(camera, movementAmount, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE);

		movementAmount.x *= collisionResult.x;
		movementAmount.y *= collisionResult.y;
		movementAmount.z *= collisionResult.z;

		camera->movePosition(movementAmount);
	}
	if (display->checkKey(SDLK_a))
	{
		glm::vec3 left = glm::cross(camera->getForward(), camera->getUp());

		glm::fvec3 movementAmount(left.x * -0.1, left.y * -0.1, left.z * -0.1);

		//glm::fvec3 collisionResult = myScene->checkCollisionCamera(cameraObject, movementAmount, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE);
		glm::fvec3 collisionResult = checkCollisionCameraWalls(camera, movementAmount, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE);

		movementAmount.x *= collisionResult.x;
		movementAmount.y *= collisionResult.y;
		movementAmount.z *= collisionResult.z;

		camera->movePosition(movementAmount);
	}

	camera->rotateY(camera->getSensitivity() * display->getMouseDifX());

	if (display->checkKeyDown(SDLK_f))
	{
		if (isAtExit())
		{
			//finishLevel();
			return;
		}

		for (int i = 0; i < doors.size(); i++)
		{
			//If close to door and looking at it
			if (abs(doors.at(i)->getTransform()->GetPos().x - camera->getPosition().x) < doors.at(i)->DOOR_OPEN_RANGE &&
				abs(doors.at(i)->getTransform()->GetPos().z - camera->getPosition().z) < doors.at(i)->DOOR_OPEN_RANGE)
			{
				doors.at(i)->open();
			}
		}
	}

	if (display->checkMouseDown(0))
	{
		glm::fvec2 lineStart(camera->getPosition().x, camera->getPosition().z);
		glm::fvec2 castDirection(camera->getForward().x, camera->getForward().z);
		castDirection = glm::normalize(castDirection);
		glm::fvec2 lineEnd = lineStart + castDirection * camera->SHOOT_DISTANCE;

		glm::fvec2 collisionVector;
		bool hitSomething = checkIntersection(&collisionVector, lineStart, lineEnd, true);
	}
}

//void TestScene::finishLevel()
//{
//	loadNextLevel = true;
//}
//bool TestScene::isFinished()
//{
//	return loadNextLevel;
//}

std::vector<Monster*>* TestScene::getMonsters()
{
	return &monsters;
}

//void TestScene::setIsRunning(bool value)
//{
//	isRunning = value;
//}

bool TestScene::isAtExit()
{
	for (int i = 0; i < exits.size(); i++)
	{
		if (((int)camera->getPosition().x / SPOT_WIDTH) == exits.at(i)->x &&
			((int)camera->getPosition().z / SPOT_DEPTH) == exits.at(i)->y)
		{
			return true;
		}
	}

	return false;
}

std::vector<Door*>* TestScene::getDoors()
{
	return &doors;
}

bool TestScene::checkIntersection(glm::fvec2* result, glm::fvec2 lineStart, glm::fvec2 lineEnd, bool hurtMonsters)
{
	//Find nearest intersection to the start of the line
	glm::fvec2 nearestInterestion(0, 0);
	bool foundOne = false;
	bool collides;

	for (int i = 0; i < collisionPosStart.size(); i++)
	{
		glm::fvec2 collisionVector;
		collides = lineIntersect(&collisionVector, lineStart, lineEnd, *collisionPosStart.at(i), *collisionPosEnd.at(i));

		if (((!foundOne && collides) || (collides && (getLineLength(nearestInterestion - lineStart) > getLineLength(collisionVector - lineStart)))))
		{
			foundOne = true;
			//std::cout << i << ": " << collisionVector.x << " : " << collisionVector.y << " \n";
			nearestInterestion = collisionVector;
		}
	}

	for (int i = 0; i < doors.size(); i++)
	{
		glm::fvec2 doorSize(SPOT_WIDTH, SPOT_DEPTH);
		//glm::fvec2 doorPos2f(doors.at(i)->getDimensions().x, doors.at(i)->getDimensions().z);
		glm::fvec2 doorPos2f(doors.at(i)->getTransform()->GetPos().x, doors.at(i)->getTransform()->GetPos().z);

		glm::fvec2 collisionVector;
		bool intersects = lineInterestRect(&collisionVector, lineStart, lineEnd, doorPos2f, doorSize);

		if (intersects)
		{
			if (!foundOne)
			{
				nearestInterestion = collisionVector;
				foundOne = true;
			}
			else
			{
				nearestInterestion = findNearestVector2(nearestInterestion, collisionVector, lineStart);
			}
		}
	}

	if (!foundOne)
	{
		return false;
	}

	if (hurtMonsters)
	{
		glm::fvec2 neareastMonsterIntersect(0, 0);
		Monster* nearestMonster = nullptr;

		//Find a monster it is hitting
		for (int i = 0; i < monsters.size(); i++)
		{
			glm::fvec2 doorSize(monsters.at(i)->getDimensions().x, monsters.at(i)->getDimensions().z);
			glm::fvec2 doorPos2f(monsters.at(i)->getTransform()->GetPos().x, monsters.at(i)->getTransform()->GetPos().z);

			glm::fvec2 collisionVector;
			bool didCollide = lineInterestRect(&collisionVector, lineStart, lineEnd, doorPos2f, doorSize);

			glm::fvec2 lastInter = neareastMonsterIntersect;
			neareastMonsterIntersect = findNearestVector2(nearestInterestion, collisionVector, lineStart);

			if (didCollide && lastInter != neareastMonsterIntersect)
			{
				nearestMonster = monsters.at(i);
			}
		}

		if (nearestMonster != nullptr)
		{
			std::cout << "Monster hit\n";
			nearestMonster->damage(camera->PLAYER_DAMAGE);
		}
	}

	result->x = nearestInterestion.x;
	result->y = nearestInterestion.y;
	return true;
	//return nearestInterestion;
}

glm::fvec3 TestScene::checkCollisionEnemyWalls(Monster* monster, glm::fvec3 movement, float objectWidth, float objectHeight, float objectDepth)
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

glm::fvec3 TestScene::checkCollisionCameraWalls(Camera* camera, glm::fvec3 movement, float objectWidth, float objectHeight, float objectDepth)
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
	int camInX = (camera->getPosition().x) / (SPOT_WIDTH)+0.5 * SPOT_WIDTH;
	int camInZ = (camera->getPosition().z) / (SPOT_DEPTH)+0.5 * SPOT_DEPTH;
	int camWantGoX = (camera->getPosition().x + movement.x + offsetX) / (SPOT_WIDTH)+0.5 * SPOT_WIDTH;
	int camWantGoZ = (camera->getPosition().z + movement.z + offsetZ) / (SPOT_DEPTH)+0.5 * SPOT_DEPTH;

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

void TestScene::addSpecial(int blueValue, int x, int z)
{
	//Add door
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

	if (blueValue == 1)
	{
		//Set the starting position.
		camera->setPosition(glm::fvec3(x * SPOT_WIDTH, 0.5 * SPOT_HEIGHT, z * SPOT_DEPTH));
	}
	if (blueValue == 128)
	{
		//Add a monster
		float XLow, XHigh, YLow, YHigh;
		//level->calcTexCoords(79, NUM_TEXTURES, NUM_TEX_EXP, &XLow, &XHigh, &YLow, &YHigh);
		Monster* tempDoor = new Monster("Monster" + std::to_string(x) + "_" + std::to_string(z), Monster::SIZEX, Monster::SIZEY, 0, 0, 1, 0, 1, TextureManager::getTextureManager()->getTexture("SSWVA1"), ShaderManager::getShaderManager()->getShader("Phong"), camera, this);
		addGameObjectToScene(tempDoor);
		getGameObject("Monster" + std::to_string(x) + "_" + std::to_string(z))->setTransform(Vec9::createVec9(x * SPOT_WIDTH, 0.5 * SPOT_HEIGHT - 0.25 * Monster::SIZEY, z * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
		monsters.push_back(tempDoor);
		tempDoor->addTexture(TextureManager::getTextureManager()->getTexture("SSWVA1"));
		tempDoor->addTexture(TextureManager::getTextureManager()->getTexture("SSWVB1"));
		tempDoor->addTexture(TextureManager::getTextureManager()->getTexture("SSWVC1"));
		tempDoor->addTexture(TextureManager::getTextureManager()->getTexture("SSWVD1"));
		tempDoor->addTexture(TextureManager::getTextureManager()->getTexture("SSWVE0"));
		tempDoor->addTexture(TextureManager::getTextureManager()->getTexture("SSWVF0"));
		tempDoor->addTexture(TextureManager::getTextureManager()->getTexture("SSWVG0"));
		tempDoor->addTexture(TextureManager::getTextureManager()->getTexture("SSWVH0"));
		tempDoor->addTexture(TextureManager::getTextureManager()->getTexture("SSWVI0"));
		tempDoor->addTexture(TextureManager::getTextureManager()->getTexture("SSWVJ0"));
		tempDoor->addTexture(TextureManager::getTextureManager()->getTexture("SSWVK0"));
		tempDoor->addTexture(TextureManager::getTextureManager()->getTexture("SSWVL0"));
		tempDoor->addTexture(TextureManager::getTextureManager()->getTexture("SSWVM0"));
	}
	if (blueValue == 192)
	{
		//Add a medkit
		float XLow, XHigh, YLow, YHigh;
		//level->calcTexCoords(79, NUM_TEXTURES, NUM_TEX_EXP, &XLow, &XHigh, &YLow, &YHigh);
		Medkit* tempDoor = new Medkit("Medkit" + std::to_string(x) + "_" + std::to_string(z), Medkit::SIZEX, Medkit::SIZEY, 0, 0, 1, 0, 1, TextureManager::getTextureManager()->getTexture("Medkit"), ShaderManager::getShaderManager()->getShader("Phong"), camera, this);
		addGameObjectToScene(tempDoor);
		getGameObject("Medkit" + std::to_string(x) + "_" + std::to_string(z))->setTransform(Vec9::createVec9(x * SPOT_WIDTH, 0.5 * Medkit::SIZEY, z * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
		medkits.push_back(tempDoor);
	}
	if (blueValue == 97)
	{
		exits.push_back(new glm::vec2(x, z));
	}
}

void TestScene::generateLevel(std::string fileName)
{
	//level = new Bitmap(".\\res\\Level1.png");
	level = new Bitmap(fileName);
	level->flipX();
	level->flipY();

	//TEST
	float XLow, XHigh, YLow, YHigh;

	HUD = GameObject::createCubePartTexture("HUD", 0.2, 0.2, 0, 1, 0, 1, 0, TextureManager::getTextureManager()->getTexture("Gun0"), ShaderManager::getShaderManager()->getShader("Basic"));
	HUD->getTransform()->SetPos(glm::fvec3(17, 0.12 * SPOT_HEIGHT, 17));

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
			level->calcTexCoords(level->getPixel(i, j).g, NUM_TEXTURES, NUM_TEX_EXP, &XLow, &XHigh, &YLow, &YHigh);

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
				collisionPosStart.push_back(new glm::fvec2(i * SPOT_WIDTH, (j)* SPOT_DEPTH));
				collisionPosEnd.push_back(new glm::fvec2((i)* SPOT_WIDTH, (j + 1) * SPOT_DEPTH));

				addGameObjectToScene(GameObject::createCubePartTexture(name + "_Wall_c_" + std::to_string(i) + "_" + std::to_string(j), 0, SPOT_HEIGHT, SPOT_DEPTH, XLow, XHigh, YLow, YHigh, TextureManager::getTextureManager()->getTexture("Wolf"), ShaderManager::getShaderManager()->getShader("Phong")));
				getGameObject(name + "_Wall_c_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9((i - 0.5) * SPOT_WIDTH, SPOT_HEIGHT / 2, (j)* SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
			}
			if (level->getPixel(i + 1, j).r == 0 && level->getPixel(i + 1, j).g == 0 && level->getPixel(i + 1, j).b == 0)
			{
				collisionPosStart.push_back(new glm::fvec2((i + 1) * SPOT_WIDTH, (j)* SPOT_DEPTH));
				collisionPosEnd.push_back(new glm::fvec2((i + 1) * SPOT_WIDTH, (j + 1) * SPOT_DEPTH));

				addGameObjectToScene(GameObject::createCubePartTexture(name + "_Wall_d_" + std::to_string(i) + "_" + std::to_string(j), 0, SPOT_HEIGHT, SPOT_DEPTH, XLow, XHigh, YLow, YHigh, TextureManager::getTextureManager()->getTexture("Wolf"), ShaderManager::getShaderManager()->getShader("Phong")));
				getGameObject(name + "_Wall_d_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9((i + 0.5) * SPOT_WIDTH, SPOT_HEIGHT / 2, (j)* SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
			}
		}
	}
}