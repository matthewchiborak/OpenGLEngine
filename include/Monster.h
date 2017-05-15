#ifndef __MONSTER_H
#define __MONSTER_H

#include "GameObject.h"

class Monster : public GameObject
{
public:
	Monster(std::string name, float width, float height, float depth, float XLower, float XHigher, float YLower, float YHigher, Texture* texture, Shader* shader);
	~Monster();

	void update();

	//Enable ability for monster functionallity
	void init();

	static float SIZEX;
	static float SIZEY;

private:

};

#endif