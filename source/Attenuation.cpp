#include "../include/Attenuation.h"

Attenuation::Attenuation()
{
	this->constant = 1;
	this->linear = 1;
	this->exponent = 1;
}
Attenuation::Attenuation(float constant, float linear, float exponent)
{
	this->constant = constant;
	this->linear = linear;
	this->exponent = exponent;
}

Attenuation::~Attenuation()
{
}

void Attenuation::setConstant(float value)
{
	constant = value;
}
void Attenuation::setLinear(float value)
{
	linear = value;
}
void Attenuation::setExponent(float value)
{
	exponent = value;
}
float Attenuation::getConstant()
{
	return constant;
}
float Attenuation::getLinear()
{
	return linear;
}
float Attenuation::getExponent()
{
	return exponent;
}