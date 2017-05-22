#ifndef __MONSTER_H
#define __MONSTER_H

#include <vector>
#include "GameObject.h"
//#include "Scene.h"
#include "TestScene.h"

//class Scene;
class TestScene;

class Monster : public GameObject
{
public:
	Monster(std::string name, float width, float height, float depth, float XLower, float XHigher, float YLower, float YHigher, Texture* texture, Shader* shader, Camera* camera, TestScene* myScene);
	~Monster();

	void update();

	//Enable ability for monster functionallity
	void init();

	void damage(int amt);

	void addTexture(Texture* texture);

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
	TestScene* myScene;

	const float MOVE_SPEED = 0.01;
	const float MOVEMENT_STOP_DISTANCE = 1.5;
	const float SHOOT_DISTANCE = 1000.0f;
	int random;
	bool canLook;
	std::chrono::high_resolution_clock::time_point lastIdle;
	std::chrono::high_resolution_clock::time_point lastAttack;
	std::chrono::high_resolution_clock::time_point lastChase;
	std::chrono::high_resolution_clock::time_point dyingTime;
	const float attackConstant = 5;
	std::chrono::high_resolution_clock::time_point lastAttackStart;
	bool canAttack;
	int health;
	const int MAX_HEALTH = 100;
	const int MONSTER_DAMAGE = 10;

	std::vector<Texture*> textures;
};

#endif