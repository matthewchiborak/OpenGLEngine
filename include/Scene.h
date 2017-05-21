#ifndef __SCENE_H
#define __SCENE_H

#include <string>
#include <vector>

#include "GameObject.h"
#include "Input.h"
#include "Camera.h"
#include "Display.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "Bitmap.h"
#include "Time.h"
#include "Door.h"
#include "Monster.h"
#include "Medkit.h"

#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/glm.hpp>

class Input;
class Monster;
class Medkit;

class Scene
{
public:
	Scene(std::string name, float windowWidth, float windowHeight);
	Scene(std::string name, std::string fileName, float windowWidth, float windowHeight);
	~Scene();
	std::string getName();
	void addGameObjectToScene(GameObject* object);
	void addInputToScene(Input* input);
	GameObject* getGameObject(std::string name);
	void update(Display* display);
	void moveCamera(Vec9 atLookUp);
	void resetCamera(Vec9 atLookUp);
	void setPerspective(float fov, float aspect, float zNear, float zFar);
	Camera* getCamera();
	void setNewCamera(Camera* camera);

	std::vector<Door*>* getDoors();
	std::vector<Monster*>* getMonsters();
	std::vector<glm::vec2*> exits;

	bool isAtExit();

	//Vec3 for each axis. 1 is theres a collision
	glm::fvec3 checkCollisionCamera(Camera* camera, glm::fvec3 movement, float objectWidth, float objectHeight, float objectDepth);
	glm::fvec3 rectCollide(glm::fvec3 oldPos, glm::fvec3 newPos, glm::fvec3 size1, glm::fvec3 size2, glm::fvec3 pos2);
	glm::fvec3 checkCollisionCameraWalls(Camera* camera, glm::fvec3 movement, float objectWidth, float objectHeight, float objectDepth);

	glm::fvec3 checkCollisionEnemyWalls(Monster* monster, glm::fvec3 movement, float objectWidth, float objectHeight, float objectDepth);

	bool checkIntersection(glm::fvec2* result, glm::fvec2 lineStart, glm::fvec2 lineEnd, bool hurtMonsters);
	bool lineInterestRect(glm::fvec2* resultStore, glm::fvec2 lineStart, glm::fvec2 lineEnd);
	float getLineLength(glm::fvec2 line);

	glm::fvec2 findNearestVector2(glm::fvec2 a, glm::fvec2 b, glm::fvec2 positionRelativeTo);

	bool lineInterestRect(glm::fvec2* resultStore, glm::fvec2 lineStart, glm::fvec2 lineEnd, glm::fvec2 pos, glm::fvec2 size);

	static float PLAYER_SIZE;

	static void setIsRunning(bool value);

	const float SPOT_WIDTH = 1;
	const float SPOT_HEIGHT = 1;
	const float SPOT_DEPTH = 1;

	void finishLevel();
	bool isFinished();

private:
	static bool isRunning;

	std::string name;
	Camera* camera;
	GameObject* HUD;
	std::vector<GameObject*> gameObjects;
	std::vector<Input*> inputs;
	std::vector<Door*> doors;
	std::vector<Monster*> monsters;
	std::vector<Medkit*> medkits;

	Bitmap* level;
	long lastTimeUpdated;

	static int NUM_TEX_EXP;
	static int NUM_TEXTURES;
	const float DOOR_THICKNESS = 0.125f;

	//For line interestion
	std::vector<glm::fvec2*> collisionPosStart;
	std::vector<glm::fvec2*> collisionPosEnd;

	void generateLevel(std::string fileName);

	void addSpecial(int blueValue, int x, int z);

	bool lineIntersect(glm::fvec2* resultStore, glm::fvec2 lineStart1, glm::fvec2 lineEnd1, glm::fvec2 lineStart2, glm::fvec2 lineEnd2);

	
	float crossProduct(glm::fvec2 a, glm::fvec2 b);

	bool loadNextLevel;
};

#endif