#ifndef __MONSTER_H
#define __MONSTER_H

#include "GameObject.h"
#include "Scene.h"

class Scene;

class Monster : public GameObject
{
public:
	Monster(std::string name, float width, float height, float depth, float XLower, float XHigher, float YLower, float YHigher, Texture* texture, Shader* shader, Camera* camera, Scene* myScene);
	~Monster();

	void update();

	//Enable ability for monster functionallity
	void init();

	void damage(int amt);

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
	Scene* myScene;

	const float MOVE_SPEED = 0.01;
	const float MOVEMENT_STOP_DISTANCE = 1.5;
	const float SHOOT_DISTANCE = 1000.0f;
	int random;
	bool canLook;
	std::chrono::high_resolution_clock::time_point lastIdle;
	std::chrono::high_resolution_clock::time_point lastAttack;
	const float attackConstant = 5;
	std::chrono::high_resolution_clock::time_point lastAttackStart;
	bool canAttack;
	int health;
	const int MAX_HEALTH = 100;
	const int MONSTER_DAMAGE = 10;
};

#endif