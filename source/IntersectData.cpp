#include "../include/IntersectData.h"

IntersectData::IntersectData(bool doesIntersect, float distance)
{
	this->doesIntersect = doesIntersect;
	this->distance = distance;
}

IntersectData::~IntersectData()
{
}

void IntersectData::setDoesIntersect(bool status)
{
	this->doesIntersect = status;
}
void IntersectData::setDistance(float distance)
{
	this->distance = distance;
}
bool IntersectData::getDoesIntersect()
{
	return doesIntersect;
}
float IntersectData::getDistance()
{
	return distance;
}