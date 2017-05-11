#include "../include/BaseLight.h"

BaseLight::BaseLight()
{

}

BaseLight::BaseLight(glm::fvec3 color, float intensity)
{
	this->color = color;
	this->intensity = intensity;
}

BaseLight::~BaseLight()
{
}

void BaseLight::setColor(glm::fvec3 color)
{
	this->color = color;
}
glm::fvec3 BaseLight::getColor()
{
	return color;
}
void BaseLight::setIntensity(float intensity)
{
	this->intensity = intensity;
}
float BaseLight::getIntensity()
{
	return intensity;
}