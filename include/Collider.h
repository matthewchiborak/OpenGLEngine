#ifndef __COLLIDER_H
#define __COLLIDER_H

#include "IntersectData.h"

class Collider
{
public:
	Collider();
	Collider(int type);
	~Collider();

	enum ColliderType
	{
		TYPE_SPHERE,
		TYPE_AABB,

		TYPE_SIZE
	};

	void setType(int type);
	int getType();

	virtual IntersectData intersect(Collider* other);
	virtual void transform(glm::fvec3 translation);
	virtual glm::fvec3 getCenter();
	virtual void setCenter(glm::fvec3 center);

protected:
	int type;
};

#endif