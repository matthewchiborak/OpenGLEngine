#ifndef __PLANE_H
#define __PLANE_H

#include "IntersectData.h"
#include "BoundingSphere.h"

class Plane
{
public:
	Plane(glm::fvec3 normal, float distance);
	~Plane();

	glm::fvec3 getNormal();
	float getDistance();

	Plane normalized();
	IntersectData intersectSphere(BoundingSphere* other);

private:
	glm::fvec3 normal;
	float distance;
};

#endif