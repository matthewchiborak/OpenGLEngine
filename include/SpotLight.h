#ifndef __SPOTLIGHT_H
#define __SPOTLIGHT_H

#include "PointLight.h"

class SpotLight
{
public:
	SpotLight();
	SpotLight(glm::fvec3 color, float intensity, glm::fvec3 position, float constant, float linear, float exponent, glm::fvec3 direction, float cutoff);
	~SpotLight();

	void setPointLight(glm::fvec3 position, float range, glm::fvec3 color, float intensity, float constant, float linear, float exponent);
	void setDirection(glm::fvec3 direction);
	void setCutoff(float cutoff);
	PointLight getPointLight();
	glm::fvec3 getDirection();
	float getCutoff();

	void setOffset(glm::fvec3 offset);
	glm::fvec3 getTotalPosition();

private:
	PointLight pointLight;
	glm::fvec3 direction;
	glm::fvec3 offset;
	float cutoff;
};

#endif