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

void PhysicsEngine::simulate(double delta)
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

			//Collision occurred
			if (intersectData.getDoesIntersect())
			{
				glm::fvec3 direction = intersectData.getDirection() / intersectData.getDistance();
				//glm::fvec3 otherDirection = direction.Reflect(objects.at(i)->getVelocity().normalized);
				float directionMagnitude = sqrtf((objects.at(i)->getVelocity().x * objects.at(i)->getVelocity().x)
					+ (objects.at(i)->getVelocity().y * objects.at(i)->getVelocity().y)
					+ (objects.at(i)->getVelocity().z * objects.at(i)->getVelocity().z));

				glm::fvec3 tempDirection = objects.at(i)->getVelocity() / directionMagnitude;
				float reflect = 2 * ((direction.x * tempDirection.x) + (direction.y * tempDirection.y) + (direction.z * tempDirection.z));

				glm::fvec3 otherDirection = direction - (tempDirection * reflect);

				//Now to set the new velocities
				//glm::fvec3 newVelo1 = objects.at(i)->getVelocity().reflect(otherDirection);
				float reflect2 = 2 * ((objects.at(i)->getVelocity().x * otherDirection.x) + (objects.at(i)->getVelocity().y * otherDirection.y) + (objects.at(i)->getVelocity().z * otherDirection.z));
				glm::fvec3 newVelo1 = objects.at(i)->getVelocity() - (otherDirection * reflect2);
				objects.at(i)->setVelocity(newVelo1);

				float reflect3 = 2 * ((objects.at(j)->getVelocity().x * direction.x) + (objects.at(j)->getVelocity().y * direction.y) + (objects.at(j)->getVelocity().z * direction.z));
				glm::fvec3 newVelo2 = objects.at(j)->getVelocity() - (direction * reflect3);
				objects.at(j)->setVelocity(newVelo2);

				//objects.at(i)->setVelocity()
				//objects.at(j)->reflect(direction);
				std::cout << "HIT: Velo1: " << newVelo1.x << ", " << newVelo1.y << ", " << newVelo1.z << " | Velo2: " << newVelo2.x << ", " << newVelo2.y << ", " << newVelo2.z << "\n";
			}
		}
	}
}

void PhysicsEngine::clear()
{
	objects.clear();
}