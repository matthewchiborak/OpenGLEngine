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

private:
	glm::fvec3 position;
	glm::fvec3 oldPosition;
	glm::fvec3 velocity;

	Collider* collider;
};

#endif