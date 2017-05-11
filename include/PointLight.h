#ifndef __POINTLIGHT_H
#define __POINTLIGHT_H

#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/glm.hpp>

#include "BaseLight.h"
#include "Attenuation.h"

class PointLight
{
public:
	PointLight();
	~PointLight();

	void setBaseLight(glm::fvec3 color, float intensity);
	void setAtten(float constant, float linear, float exponent);
	void setPosition(glm::fvec3 position);

	glm::fvec3 getBaseColor();
	float getBaseIntensity();
	glm::fvec3 getPosition();
	float getConstant();
	float getLinear();
	float getExponent();

private:
	BaseLight baseLight;
	Attenuation atten;
	glm::fvec3 position;
};

#endif