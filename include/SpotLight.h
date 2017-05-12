#ifndef __SPOTLIGHT_H
#define __SPOTLIGHT_H

#include "PointLight.h"

class SpotLight
{
public:
	SpotLight();
	~SpotLight();

	void setPointLight(glm::fvec3 position, float range, glm::fvec3 color, float intensity, float constant, float linear, float exponent);
	void setDirection(glm::fvec3 direction);
	void setCutoff(float cutoff);
	PointLight getPointLight();
	glm::fvec3 getDirection();
	float getCutoff();

private:
	PointLight pointLight;
	glm::fvec3 direction;
	float cutoff;
};

#endif