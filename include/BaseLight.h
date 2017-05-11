#ifndef __BASELIGHT_H
#define __BASELIGHT_H

#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/glm.hpp>

class BaseLight
{
public:
	BaseLight();
	BaseLight(glm::fvec3 color, float intensity);
	~BaseLight();

	void setColor(glm::fvec3 color);
	glm::fvec3 getColor();
	void setIntensity(float intensity);
	float getIntensity();

private:
	glm::fvec3 color;
	float intensity;
};

#endif