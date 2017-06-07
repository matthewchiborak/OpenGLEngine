#ifndef __AABB_H
#define __AABB_H

//AXIS ALLIGNED BOUNDING BOX
#include "IntersectData.h"

class AABB
{
public:
	AABB(glm::fvec3 minExtents, glm::fvec3 maxExtents);
	~AABB();

	void setMinExtents(glm::fvec3 minExtents);
	void setMaxExtents(glm::fvec3 maxExtents);
	glm::fvec3 getMinExtents();
	glm::fvec3 getMaxExtents();

	IntersectData intersectAABB(AABB* other);

private:
	//The 2 extreme corners of the bounding box. 
	glm::fvec3 minExtents;
	glm::fvec3 maxExtents;
};

#endif