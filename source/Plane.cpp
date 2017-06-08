#include "../include/Plane.h"

Plane::Plane(glm::fvec3 normal, float distance)
{
	this->normal = normal;
	this->distance = distance;
}

Plane::~Plane()
{
}

glm::fvec3 Plane::getNormal()
{
	return normal;
}
float Plane::getDistance()
{
	return distance;
}

Plane Plane::normalized()
{
	float magnitude = normal.length();

	return Plane(normal / magnitude, distance / magnitude);
}

IntersectData Plane::intersectSphere(BoundingSphere* other)
{
	//Distance is the normal dotted with the sphere's center
	float distanceFromSphereCenter = normal.x * other->getCenter().x + normal.y * other->getCenter().y + normal.z * other->getCenter().z + distance;

	//Want the absolute value of the distance
	if (distanceFromSphereCenter < 0)
	{
		distanceFromSphereCenter *= -1;
	}

	float distanceFromSphere = distanceFromSphereCenter - other->getRadius();

	return IntersectData(distanceFromSphere < 0, normal * distanceFromSphere);
}