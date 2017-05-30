#include "../include/SpotLight.h"

SpotLight::SpotLight()
{
	direction = glm::fvec3(0, 1, 0);
	cutoff = 1;
}

SpotLight::SpotLight(glm::fvec3 color, float intensity, glm::fvec3 position, float constant, float linear, float exponent, glm::fvec3 direction, float cutoff)
{
	this->direction = direction;
	this->cutoff = cutoff;
	pointLight.setBaseLight(color, intensity);
	pointLight.setPosition(position);
	pointLight.setAtten(constant, linear, exponent);
}

SpotLight::~SpotLight()
{
}

void SpotLight::setPointLight(glm::fvec3 position, float range, glm::fvec3 color, float intensity, float constant, float linear, float exponent)
{
	pointLight.setBaseLight(color, intensity);
	pointLight.setPosition(position);
	pointLight.setRange(range);
	pointLight.setAtten(constant, linear, exponent);
}
void SpotLight::setDirection(glm::fvec3 direction)
{
	this->direction = glm::normalize(direction);
}
void SpotLight::setCutoff(float cutoff)
{
	this->cutoff = cutoff;
}
PointLight SpotLight::getPointLight()
{
	return pointLight;
}
glm::fvec3 SpotLight::getDirection()
{
	return direction;
}
float SpotLight::getCutoff()
{
	return cutoff;
}

void SpotLight::setOffset(glm::fvec3 offset)
{
	this->offset = offset;
}
glm::fvec3 SpotLight::getTotalPosition()
{
	return pointLight.getPosition() + offset;
}