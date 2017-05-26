#ifndef __GAMECOMPONENT_H
#define __GAMECOMPONENT_H

//#include "Camera.h"
#include "GameObject.h"

class GameObject;

class GameComponent
{
public:
	GameComponent();
	~GameComponent();

	void setGameObject(GameObject* gameObject);

	virtual void init();
	virtual void input(float delta);
	virtual void update(float delta);
	//void render(Camera* camera);
	virtual void render(Camera* camera);
	virtual void render(Camera* camera, Shader* shader);

	//void addToRenderingEngine();

protected:
	GameObject* gameObject;
};

#endif