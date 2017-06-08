#include "../include/IntersectData.h"

IntersectData::IntersectData(bool doesIntersect, glm::fvec3 direction)
{
	this->doesIntersect = doesIntersect;
	this->direction = direction;
}

IntersectData::~IntersectData()
{
}

void IntersectData::setDoesIntersect(bool status)
{
	this->doesIntersect = status;
}
void IntersectData::setDirection(glm::fvec3 direction)
{
	this->direction = direction;
}
bool IntersectData::getDoesIntersect()
{
	return doesIntersect;
}
glm::fvec3 IntersectData::getDirection()
{
	return direction;
}
float IntersectData::getDistance()
{
	return sqrtf((direction.x * direction.x) + (direction.y * direction.y) + (direction.z * direction.z));
}