#ifndef __PHYSICSOBJECT_H
#define __PHYSICSOBJECT_H

#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/glm.hpp>
#include "BoundingSphere.h"

//Representation of the game objects in the physics engine
class PhysicsObject
{
public:
	//PhysicsObject(glm::fvec3 position, glm::fvec3 velocity);
	PhysicsObject(Collider* collider, glm::fvec3 velocity);
	~PhysicsObject();

	void setPosition(glm::fvec3 position);
	void setVelocity(glm::fvec3 velocity);
	glm::fvec3 getPosition();
	glm::fvec3 getVelocity();

	//Based on velo and pos, update the position. 
	void integrate(double delta);

	Collider* getCollider();

	void addToPosition(glm::fvec3 pos);
	glm::fvec3 getTranslation();

	void resetPositionWithOriginalOffset(glm::fvec3 pos);

	void setLastIntersectData(IntersectData lastData);
	IntersectData getLastIntersetData();
	bool hasNewIntersectData();
	void setHadNewIntersectData(bool status);

	std::string getName();
	void setName(std::string name);

private:
	glm::fvec3 position;
	glm::fvec3 oldPosition;
	glm::fvec3 velocity;

	glm::fvec3 offset;

	glm::fvec3 translation;

	Collider* collider;

	//Might want to store the last two so can tell enter and exit collision events
	bool lastIntersectDataIsSet;
	IntersectData lastIntersectData;

	std::string name;
};

#endif