#ifndef __POINTLIGHT_H
#define __POINTLIGHT_H

#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/glm.hpp>

#include "BaseLight.h"
#include "Attenuation.h"

class PointLight
{
public:
	PointLight();
	PointLight(glm::fvec3 color, float intensity, glm::fvec3 position, float constant, float linear, float exponent);
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

	float getRange();
	void setRange(float value);

	void setOffset(glm::fvec3 offset);
	glm::fvec3 getTotalPosition();

private:
	BaseLight baseLight;
	Attenuation atten;
	glm::fvec3 position;
	glm::fvec3 offset;
	float range;

	static int COLOR_DEPTH;
};

#endif