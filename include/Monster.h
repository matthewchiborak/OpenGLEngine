#ifndef __MONSTER_H
#define __MONSTER_H

#include "GameObject.h"

class Monster : public GameObject
{
public:
	Monster(std::string name, float width, float height, float depth, float XLower, float XHigher, float YLower, float YHigher, Texture* texture, Shader* shader, Camera* camera);
	~Monster();

	void update();

	//Enable ability for monster functionallity
	void init();

	static float SIZEX;
	static float SIZEY;

	//States that the monster can be in currently
	enum STATE
	{
		IDLE,
		CHASE,
		ATTACK,
		DYING,
		DEAD
	};

private:
	void idleUpdate();
	void chaseUpdate();
	void attackUpdate();
	void dyingUpdate();
	void deadUpdate();


	int currentState;
	//Needs a ref so can always face the camera
	Camera* camera;
};

#endif