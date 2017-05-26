#ifndef __DIRECTIONALLIGHT_H
#define __DIRECTIONALLIGHT_H

#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/glm.hpp>
#include "BaseLight.h"

class DirectionalLight //: public GameComponent
{
public:
	DirectionalLight();
	DirectionalLight(glm::fvec3 direction, glm::fvec3 color, float intensity);
	~DirectionalLight();

	void setBase(glm::fvec3 color, float intensity);
	BaseLight getBaseLight();
	void setDirection(glm::fvec3 direction);
	glm::fvec3 getDirection();

private:
	BaseLight base;
	glm::fvec3 direction;
};

#endif