#ifndef __PHYSICSENGINE_H
#define __PHYSICSENGINE_H

#include <vector>

#include "PhysicsObject.h"
#include "BoundingSphere.h"

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	static PhysicsEngine* getPhysicsEngine();

	void addObject(PhysicsObject* object);
	
	void simulate(double delta);

	void handleCollisions();

private:
	static PhysicsEngine* s_instance;

	std::vector<PhysicsObject*> objects;
};

#endif