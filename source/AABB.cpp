#include "../include/AABB.h"

AABB::AABB(glm::fvec3 minExtents, glm::fvec3 maxExtents)
{
	this->minExtents = minExtents;
	this->maxExtents = maxExtents;
}

AABB::~AABB()
{
}

void AABB::setMinExtents(glm::fvec3 minExtents)
{
	this->minExtents = minExtents;
}
void AABB::setMaxExtents(glm::fvec3 maxExtents)
{
	this->maxExtents = maxExtents;
}
glm::fvec3 AABB::getMinExtents()
{
	return minExtents;
}
glm::fvec3 AABB::getMaxExtents()
{
	return maxExtents;
}

IntersectData AABB::intersectAABB(AABB* other)
{
	//If any gaps between then, cannot possibily be touching
	glm::fvec3 distances = other->getMinExtents() - maxExtents;
	glm::fvec3 distances2 = minExtents - other->getMaxExtents();

	//Find the maximum between the two in order to ensure the proper orientation
	if (distances2.x > distances.x)
	{
		distances.x = distances2.x;
	}
	if (distances2.y > distances.y)
	{
		distances.y = distances2.y;
	}
	if (distances2.z > distances.z)
	{
		distances.z = distances2.z;
	}

	//Find the maximum distance between the two boxes
	float maxDistance = distances.x;
	if (distances.y > maxDistance)
	{
		maxDistance = distances.y;
	}
	if (distances.z > maxDistance)
	{
		maxDistance = distances.z;
	}

	//If max distance is > 0, then theres some distance between them so they cant be intersecting
	return IntersectData(maxDistance < 0, maxDistance);
}