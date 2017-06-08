#include "../include/PhysicsEngine.h"

PhysicsEngine* PhysicsEngine::s_instance = 0;

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{
	for (int i = 0; i < objects.size(); i++)
	{
		if(objects.at(i) != NULL)
		delete objects.at(i);
	}
}

PhysicsEngine* PhysicsEngine::getPhysicsEngine()
{
	if (!s_instance)
	{
		s_instance = new PhysicsEngine();
	}

	return s_instance;
}

void PhysicsEngine::addObject(PhysicsObject* object)
{
	objects.push_back(object);
}

void PhysicsEngine::simulate(long delta)
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects.at(i)->integrate(delta);
		//std::cout << delta << " | ";
		//std::cout << "Pos: " << objects.at(i)->getPosition().x << ", " << objects.at(i)->getPosition().y << ", " << objects.at(i)->getPosition().z << " | Velo: " << objects.at(i)->getVelocity().x << ", " << objects.at(i)->getVelocity().y << ", " << objects.at(i)->getVelocity().z << "\n";
	}
}

void PhysicsEngine::handleCollisions()
{
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			IntersectData intersectData = objects.at(i)->getCollider()->intersect(objects.at(j)->getCollider());

			/*if (intersectData.getDoesIntersect())
			{
				std::cout << "HIT" << intersectData.getDistance() << "\n";
			}*/
		}
	}
}