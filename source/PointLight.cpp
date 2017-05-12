#include "../include/PointLight.h"

PointLight::PointLight()
{
	atten.setConstant(1);
	atten.setExponent(1);
	atten.setLinear(1);

	baseLight.setColor(glm::fvec3(0,0,0));
	baseLight.setIntensity(0);

	this->position = glm::fvec3(0,0,0);

	range = 2;
}

PointLight::~PointLight()
{
}

void PointLight::setBaseLight(glm::fvec3 color, float intensity)
{
	baseLight.setColor(color);
	baseLight.setIntensity(intensity);
}
void PointLight::setAtten(float constant, float linear, float exponent)
{
	atten.setConstant(constant);
	atten.setExponent(exponent);
	atten.setLinear(linear);
}
void PointLight::setPosition(glm::fvec3 position)
{
	this->position = position;
}

glm::fvec3 PointLight::getBaseColor()
{
	return baseLight.getColor();
}
float PointLight::getBaseIntensity()
{
	return baseLight.getIntensity();
}
glm::fvec3 PointLight::getPosition()
{
	return position;
}
float PointLight::getConstant()
{
	return atten.getConstant();
}
float PointLight::getLinear()
{
	return atten.getLinear();
}
float PointLight::getExponent()
{
	return atten.getExponent();
}

float PointLight::getRange()
{
	return range;
}
void PointLight::setRange(float value)
{
	range = value;
}