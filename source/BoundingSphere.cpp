#include "../include/BoundingSphere.h"

BoundingSphere::BoundingSphere()
{

}
BoundingSphere::BoundingSphere(glm::fvec3 center, float radius)
{
	setType(ColliderType::TYPE_SPHERE);
	this->radius = radius;
	this->center = center;
}

BoundingSphere::~BoundingSphere()
{
}

void BoundingSphere::setCenter(glm::fvec3 center)
{
	this->center = center;
}
void BoundingSphere::setRadius(float radius)
{
	this->radius = radius;
}
glm::fvec3 BoundingSphere::getBoundingSphereCenter()
{
	return center;
}
float BoundingSphere::getRadius()
{
	return radius;
}

IntersectData BoundingSphere::intersectBoundingSphere(BoundingSphere* other)
{
	//Determine if the 2 sphere are intersecting

	//This distance is how far the two centers are in the two spheres are touching
	float radiusDistance = radius + other->getRadius();

	//The distance between the centers of the 2 spheres
	glm::fvec3 tempCenter = other->getCenter() - center;
	/*float centerDistance = sqrtf((other->getCenter().x - center.x) * (other->getCenter().x - center.x)
	+ (other->getCenter().y - center.y) * (other->getCenter().y - center.y)
	+ (other->getCenter().z - center.z) * (other->getCenter().z - center.z));*/
	float centerDistance = sqrtf((tempCenter.x * tempCenter.x)
		+ (tempCenter.y * tempCenter.y)
		+ (tempCenter.z * tempCenter.z));

	//Get the direciton and normalize it
	glm::fvec3 direction = (other->getCenter() - center) / centerDistance;

	float distance = centerDistance - radiusDistance;

	//If the center distance is less than the radius distnace then the sphere must be touching
	if (centerDistance < radiusDistance)
	{
		return IntersectData(true, direction * distance);
	}

	return IntersectData(false, direction * distance);
}

IntersectData BoundingSphere::intersect(Collider* other)
{
	if (type == TYPE_SPHERE && other->getType() == TYPE_SPHERE)
	{
		return intersectBoundingSphere((BoundingSphere*)other);
	}

	std::cerr << "Error: Collsions not implemented between specifed colliders.\n";
	return IntersectData(false, glm::fvec3(0,0,0));
}

void BoundingSphere::transform(glm::fvec3 translation)
{
	center += translation;
}

glm::fvec3 BoundingSphere::getCenter()
{
	return center;
}