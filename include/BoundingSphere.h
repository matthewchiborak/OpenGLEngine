#ifndef __BOUNDINGSPHERE_H
#define __BOUNDINGSPHERE_H

#include "Collider.h"
#include <iostream>

class BoundingSphere : public Collider
{
public:
	BoundingSphere();
	BoundingSphere(glm::fvec3 center, float radius);
	~BoundingSphere();

	void setCenter(glm::fvec3 center);
	void setRadius(float radius);
	glm::fvec3 getBoundingSphereCenter();
	float getRadius();

	IntersectData intersectBoundingSphere(BoundingSphere* other);

	IntersectData intersect(Collider* other);
	void transform(glm::fvec3 translation);
	glm::fvec3 getCenter();

private:
	glm::fvec3 center;
	float radius;
};

#endif