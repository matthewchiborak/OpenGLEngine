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

class Input;

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

	//Vec3 for each axis. 1 is theres a collision
	glm::fvec3 checkCollisionCamera(Camera* camera, glm::fvec3 movement, float objectWidth, float objectHeight, float objectDepth);
	glm::fvec3 rectCollide(glm::fvec3 oldPos, glm::fvec3 newPos, glm::fvec3 size1, glm::fvec3 size2, glm::fvec3 pos2);
	glm::fvec3 checkCollisionCameraWalls(Camera* camera, glm::fvec3 movement, float objectWidth, float objectHeight, float objectDepth);

	static float PLAYER_SIZE;

private:
	std::string name;
	Camera* camera;
	std::vector<GameObject*> gameObjects;
	std::vector<Input*> inputs;
	std::vector<Door*> doors;
	Bitmap* level;
	long lastTimeUpdated;

	const float SPOT_WIDTH = 1;
	const float SPOT_HEIGHT = 1;
	const float SPOT_DEPTH = 1;
	static int NUM_TEX_EXP;
	static int NUM_TEXTURES;
	

	void generateLevel(std::string fileName);
};

#endif