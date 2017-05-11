#ifndef __ATTENUATION_H
#define __ATTENUATION_H

class Attenuation
{
public:
	Attenuation();
	Attenuation(float constant, float linear, float exponent);
	~Attenuation();

	void setConstant(float value);
	void setLinear(float value);
	void setExponent(float value);
	float getConstant();
	float getLinear();
	float getExponent();

private:
	float constant;
	float linear;
	float exponent;
};

#endif