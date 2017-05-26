#ifndef __RENDERINGENGINE_H
#define __RENDERINGENGINE_H

#include "GameObject.h"
#include "ShaderManager.h"
#include "ForwardAmbient.h"
#include "ForwardDirectional.h"
#include "ForwardPoint.h"

class RenderingEngine
{
public:
	RenderingEngine();
	~RenderingEngine();

	static RenderingEngine* getRenderingEngine();
	void render(GameObject* object, Camera* camera);

	glm::fvec3 getAmbientLight();
	DirectionalLight* getDirectionalLight();
	PointLight* getPointLight();

	float getSpecularIntensity();
	float getSpecularExponent();

private:
	static RenderingEngine* s_instance;

	//Forward rendering lighting
	glm::fvec3 ambientLight;

	DirectionalLight directionalLight;
	DirectionalLight directionalLight2;

	PointLight pointLight;

	float specularIntensity;
	float specularExponent;
};

#endif