#ifndef __INTERSECTDATA_H
#define __INTERSECTDATA_H

#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/glm.hpp>

class IntersectData
{
public:
	IntersectData(bool doesIntersect, float distance);
	~IntersectData();

	void setDoesIntersect(bool status);
	void setDistance(float distance);
	bool getDoesIntersect();
	float getDistance();

private:
	bool doesIntersect;
	float distance;
};

#endif