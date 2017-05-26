#include "../include/RenderingEngine.h"

RenderingEngine* RenderingEngine::s_instance = 0;

RenderingEngine::RenderingEngine()
{
	ambientLight.x = 0.2;
	ambientLight.y = 0.2;
	ambientLight.z = 0.2;

	directionalLight.setBase(glm::fvec3(1, 0, 0), 1);
	directionalLight.setDirection(glm::fvec3(1, 0, 0));

	directionalLight2.setBase(glm::fvec3(0, 0, 1), 1);
	directionalLight2.setDirection(glm::fvec3(-1, 0, 0));

	pointLight.setAtten(0, 0, 1);
	pointLight.setPosition(glm::fvec3(0, 0, 0));
	pointLight.setBaseLight(glm::fvec3(0, 1, 0), 5);
	pointLight.setRange(20);

	specularIntensity = 2;
	specularExponent = 32;
}

RenderingEngine::~RenderingEngine()
{
	if (s_instance)
	{
		delete s_instance;
	}
}

RenderingEngine* RenderingEngine::getRenderingEngine()
{
	if (!s_instance)
	{
		s_instance = new RenderingEngine();
	}

	return s_instance;
}

void RenderingEngine::render(GameObject* object, Camera* camera)
{
	//object->render(camera, ShaderManager::getShaderManager()->getShader("Phong"));
	object->render(camera, ForwardAmbient::getForwardAmbient());

	//Blend in other lighting
	glEnable(GL_BLEND);

	//Adding more color into the scene
	//Existing color * a factor + new color * a factor
	glBlendFunc(GL_ONE, GL_ONE);

	//Disable writing to the depth buffer
	glDepthMask(false);
	//Only try add on the new pixel if has the exact same value to the pixel closest to the screen.
	//Aka only do calcuations on pixels that are drawn to the screen. Avoids unessarry calcuations.
	glDepthFunc(GL_EQUAL);

	//Add the directional light
	object->render(camera, ForwardDirectional::getForwardDirectional());

	//Add the other directional light
	DirectionalLight temp = directionalLight;
	directionalLight = directionalLight2;
	directionalLight2 = temp;

	object->render(camera, ForwardDirectional::getForwardDirectional());

	temp = directionalLight2;
	directionalLight2 = directionalLight;
	directionalLight = temp;

	//Point light
	object->render(camera, ForwardPoint::getForwardPoint());

	//Reset everything
	glDepthFunc(GL_LESS);
	glDepthMask(true);
	glDisable(GL_BLEND);
}

glm::fvec3 RenderingEngine::getAmbientLight()
{
	return ambientLight;
}

DirectionalLight* RenderingEngine::getDirectionalLight()
{
	return &directionalLight;
}

float RenderingEngine::getSpecularIntensity()
{
	return specularIntensity;
}
float RenderingEngine::getSpecularExponent()
{
	return specularExponent;
}

PointLight* RenderingEngine::getPointLight()
{
	return &pointLight;
}