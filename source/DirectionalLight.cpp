#include "../include/DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	base.setColor(glm::fvec3(1, 1, 1));
	base.setIntensity(1);
	this->direction = glm::fvec3(1, 0, 0);
}
DirectionalLight::DirectionalLight(glm::fvec3 direction, glm::fvec3 color, float intensity)
{
	base.setColor(color);
	base.setIntensity(intensity);
	this->direction = glm::normalize(direction);
}

DirectionalLight::~DirectionalLight()
{
}


void DirectionalLight::setBase(glm::fvec3 color, float intensity)
{
	base.setColor(color);
	base.setIntensity(intensity);
}
BaseLight DirectionalLight::getBaseLight()
{
	return base;
}
void DirectionalLight::setDirection(glm::fvec3 direction)
{
	this->direction = glm::normalize(direction);
}
glm::fvec3 DirectionalLight::getDirection()
{
	return direction;
}