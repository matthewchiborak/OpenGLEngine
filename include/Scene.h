#ifndef __SCENE_H
#define __SCENE_H

#include <string>
#include <vector>

#include "GameObject.h"
#include "Input.h"
#include "Camera.h"
#include "Display.h"

class Scene
{
public:
	Scene(std::string name, float windowWidth, float windowHeight);
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

private:
	std::string name;
	Camera* camera;
	std::vector<GameObject*> gameObjects;
	std::vector<Input*> inputs;
};

#endif