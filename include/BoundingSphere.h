#ifndef __BOUNDINGSPHERE_H
#define __BOUNDINGSPHERE_H

#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/glm.hpp>
#include "IntersectData.h"

class BoundingSphere
{
public:
	BoundingSphere(glm::fvec3 center, float radius);
	~BoundingSphere();

	void setCenter(glm::fvec3 center);
	void setRadius(float radius);
	glm::fvec3 getCenter();
	float getRadius();

	IntersectData intersectBoundingSphere(BoundingSphere* other);

private:
	glm::fvec3 center;
	float radius;
};

#endif