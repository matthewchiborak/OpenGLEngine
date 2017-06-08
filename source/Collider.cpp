#include "../include/Collider.h"

Collider::Collider()
{

}

Collider::Collider(int type)
{
	this->type = type;
}

Collider::~Collider()
{
}

void Collider::setType(int type)
{
	this->type = type;
}
int Collider::getType()
{
	return type;
}

IntersectData Collider::intersect(Collider* other)
{
	//if (type == TYPE_SPHERE && other->getType() == TYPE_SPHERE)
	//{
	//	//BoundingSph
	//}
	return IntersectData(false, glm::fvec3(0,0,0));
}

void Collider::transform(glm::fvec3 translation)
{

}

glm::fvec3 Collider::getCenter()
{
	return glm::fvec3(0, 0, 0);
}