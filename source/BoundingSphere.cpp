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
	float centerDistance = sqrtf((other->getCenter().x - center.x) * (other->getCenter().x - center.x)
	+ (other->getCenter().y - center.y) * (other->getCenter().y - center.y)
	+ (other->getCenter().z - center.z) * (other->getCenter().z - center.z));

	//If the center distance is less than the radius distnace then the sphere must be touching
	if (centerDistance < radiusDistance)
	{
		return IntersectData(true, centerDistance - radiusDistance);
	}

	return IntersectData(false, centerDistance - radiusDistance);
}

IntersectData BoundingSphere::intersect(Collider* other)
{
	if (type == TYPE_SPHERE && other->getType() == TYPE_SPHERE)
	{
		return intersectBoundingSphere((BoundingSphere*)other);
	}

	std::cerr << "Error: Collsions not implemented between specifed colliders.\n";
	return IntersectData(false, 0);
}

void BoundingSphere::transform(glm::fvec3 translation)
{
	center += translation;
}

glm::fvec3 BoundingSphere::getCenter()
{
	return center;
}