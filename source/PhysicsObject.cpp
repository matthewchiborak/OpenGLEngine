#include "../include/PhysicsObject.h"

//PhysicsObject::PhysicsObject(glm::fvec3 position, glm::fvec3 velocity)
//{
//	this->position = position;
//	this->velocity = velocity;
//	oldPosition = position;
//	collider = new 
//}
PhysicsObject::PhysicsObject(Collider* collider, glm::fvec3 velocity)
{
	this->collider = collider;
	this->velocity = velocity;
	this->position = collider->getCenter();
	this->oldPosition = collider->getCenter();
	this->offset = collider->getCenter();
}

PhysicsObject::~PhysicsObject()
{
	if (collider != NULL)
	{
		delete collider;
	}
}

void PhysicsObject::setPosition(glm::fvec3 position)
{
	this->position = position;
}
void PhysicsObject::setVelocity(glm::fvec3 velocity)
{
	this->velocity = velocity;
}
glm::fvec3 PhysicsObject::getPosition()
{
	return position;
}
glm::fvec3 PhysicsObject::getVelocity()
{
	return velocity;
}

void PhysicsObject::integrate(double delta)
{
	position.x += velocity.x * delta;
	position.y += velocity.y * delta;
	position.z += velocity.z * delta;
}

Collider* PhysicsObject::getCollider()
{
	//glm::fvec3 
	translation = position - oldPosition;
	oldPosition = position;

	collider->transform(translation);
	return collider;
}

void PhysicsObject::addToPosition(glm::fvec3 pos)
{
	position += pos;
	oldPosition += pos;

	collider->transform(pos);
}

glm::fvec3 PhysicsObject::getTranslation()
{
	return translation;
}

void PhysicsObject::resetPositionWithOriginalOffset(glm::fvec3 pos)
{
	position = pos + offset;
	collider->setCenter(position);
}