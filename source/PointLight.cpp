#include "../include/PointLight.h"

int PointLight::COLOR_DEPTH = 256;

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

PointLight::PointLight(glm::fvec3 color, float intensity, glm::fvec3 position, float constant, float linear, float exponent)
{
	this->baseLight.setColor(color);
	this->baseLight.setIntensity(intensity);
	this->position = position;
	this->setAtten(constant, linear, exponent);
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

	float max = baseLight.getColor().x;
	if (baseLight.getColor().y > max)
	{
		max = baseLight.getColor().y;
	}
	if (baseLight.getColor().z > max)
	{
		max = baseLight.getColor().z;
	}

	float c = constant - (COLOR_DEPTH * baseLight.getIntensity() * max);
	range = (-linear + sqrt(linear * linear - 4 * exponent * c)) / (2 * exponent);
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

void PointLight::setOffset(glm::fvec3 offset)
{
	this->offset = offset;
}
glm::fvec3 PointLight::getTotalPosition()
{
	return position + offset;
}