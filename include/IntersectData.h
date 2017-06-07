#ifndef __INTERSECTDATA_H
#define __INTERSECTDATA_H

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