#ifndef __DOOR_H
#define __DOOR_H

#include "GameObject.h"

class Door : public GameObject
{
public:
	Door(std::string name, float width, float height, float depth, float XLower, float XHigher, float YLower, float YHigher, Texture* texture, Shader* shader);
	~Door();

private:


};

#endif