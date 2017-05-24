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
	virtual void input();
	virtual void update();
	//void render(Camera* camera);
	virtual void render(Camera* camera);

protected:
	GameObject* gameObject;
};

#endif