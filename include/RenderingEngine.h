#ifndef __RENDERINGENGINE_H
#define __RENDERINGENGINE_H

#include "GameObject.h"
#include "ShaderManager.h"
#include "ForwardAmbient.h"
#include "ForwardDirectional.h"
#include "ForwardPoint.h"
#include "ForwardSpot.h"

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
	SpotLight* getSpotLight();

	float getSpecularIntensity();
	float getSpecularExponent();

private:
	static RenderingEngine* s_instance;

	//Forward rendering lighting
	glm::fvec3 ambientLight;

	DirectionalLight* directionalLight;
	std::vector<DirectionalLight*> directionalLights;

	PointLight* pointLight;
	std::vector<PointLight*> pointLights;

	SpotLight* spotLight;
	std::vector<SpotLight*> spotLights;

	float specularIntensity;
	float specularExponent;
};

#endif