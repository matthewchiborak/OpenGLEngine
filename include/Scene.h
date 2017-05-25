#ifndef __SCENE_H
#define __SCENE_H

#include <string>
#include <vector>

#include "GameObject.h"
#include "Camera.h"
#include "Display.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "Bitmap.h"
#include "Time.h"

#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/glm.hpp>

class Scene
{
public:
	Scene();
	Scene(std::string name, float windowWidth, float windowHeight);
	Scene(std::string name, std::string fileName, float windowWidth, float windowHeight);
	~Scene();
	std::string getName();
	void addGameObjectToScene(GameObject* object);

	GameObject* getGameObject(std::string name);
	//void baseUpdate();
	void moveCamera(Vec9 atLookUp);
	void resetCamera(Vec9 atLookUp);
	void setPerspective(float fov, float aspect, float zNear, float zFar);
	Camera* getCamera();
	void setNewCamera(Camera* camera);

	const float SPOT_WIDTH = 1;
	const float SPOT_HEIGHT = 1;
	const float SPOT_DEPTH = 1;

	virtual void init();

	void assignInfo(std::string name, int width, int height);

	//void baseInput(Display* display);
	//void baseRender();

	GameObject* getRootObject();
	void update(float delta);
	void input(Display* display, float delta);

protected:
	std::string name;
	Camera* camera;
	GameObject* HUD;
	std::vector<GameObject*> gameObjects;

	long lastTimeUpdated;

	static int NUM_TEX_EXP;
	static int NUM_TEXTURES;

	GameObject root;
	
	/*virtual void update();
	virtual void input(Display* display);
	virtual void render();*/
	
};

#endif