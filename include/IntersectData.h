#ifndef __INTERSECTDATA_H
#define __INTERSECTDATA_H

#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/glm.hpp>
#include <string>

class IntersectData
{
public:
	IntersectData();
	IntersectData(bool doesIntersect, glm::fvec3 direction);
	~IntersectData();

	void setDoesIntersect(bool status);
	void setDirection(glm::fvec3 direction);
	bool getDoesIntersect();
	glm::fvec3 getDirection();
	float getDistance();

	std::string colliderName;

private:
	bool doesIntersect;
	//float distance;
	//Direction and magnitude of the collision
	glm::fvec3 direction;
};

#endif