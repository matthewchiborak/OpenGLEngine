#include "../include/RenderingEngine.h"

RenderingEngine* RenderingEngine::s_instance = 0;

RenderingEngine::RenderingEngine()
{
	ambientLight.x = 0.2;
	ambientLight.y = 0.2;
	ambientLight.z = 0.2;

	specularIntensity = 2;
	specularExponent = 32;

	/*SpotLight* temp = new SpotLight();
	spotLights.push_back(temp);
	temp->setPointLight(glm::fvec3(0, 0, 0), 10, glm::fvec3(1, 1, 1), 10, 0, 0, 0.01);
	temp->setDirection(glm::fvec3(1,0,0));
	temp->setCutoff(0.7);*/
}

RenderingEngine::~RenderingEngine()
{
	for (int i = 0; i < directionalLights.size(); i++)
	{
		delete directionalLights.at(i);
	}
	for (int i = 0; i < pointLights.size(); i++)
	{
		delete pointLights.at(i);
	}
	for (int i = 0; i < spotLights.size(); i++)
	{
		delete spotLights.at(i);
	}

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
	//Clear the list of lights and readd them
	clearLight();
	object->addToRenderingEngine();

	//object->render(camera, ShaderManager::getShaderManager()->getShader("Phong"));
	object->render(camera, ForwardAmbient::getForwardAmbient(), *object->getTransform());

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
	for (int i = 0; i < directionalLights.size(); i++)
	{
		directionalLight = directionalLights.at(i);
		object->render(camera, ForwardDirectional::getForwardDirectional(), *object->getTransform());
	}
	
	//Point light
	for (int i = 0; i < pointLights.size(); i++)
	{
		pointLight = pointLights.at(i);
		object->render(camera, ForwardPoint::getForwardPoint(), *object->getTransform());
	}

	//Spot lights
	for (int i = 0; i < spotLights.size(); i++)
	{
		spotLight = spotLights.at(i);
		object->render(camera, ForwardSpot::getForwardSpot(), *object->getTransform());
	}

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
	return directionalLight;
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
	return pointLight;
}

SpotLight* RenderingEngine::getSpotLight()
{
	return spotLight;
}

void RenderingEngine::addDirectionalLight(glm::fvec3 color, float intensity, glm::fvec3 direction)
{
	DirectionalLight* temp = new DirectionalLight();
	temp->setBase(color, intensity);
	temp->setDirection(direction);
	directionalLights.push_back(temp);
}

void RenderingEngine::addPointLight(glm::fvec3 color, float intensity, glm::fvec3 position, float range, float constant, float linear, float exponent)
{
	PointLight* temp = new PointLight();
	temp->setBaseLight(color, intensity);
	temp->setPosition(position);
	temp->setRange(range);
	temp->setAtten(constant, linear, exponent);
	pointLights.push_back(temp);
}

void RenderingEngine::addSpotLight(glm::fvec3 color, float intensity, glm::fvec3 position, float range, float constant, float linear, float exponent, glm::fvec3 direction, float cutoff)
{
	SpotLight* temp = new SpotLight();
	temp->setPointLight(position, range, color, intensity, constant, linear, exponent);
	temp->setDirection(direction);
	temp->setCutoff(cutoff);
	spotLights.push_back(temp);
}

void RenderingEngine::setAmbientLight(glm::fvec3 light)
{
	ambientLight = light;
}

void RenderingEngine::addDirectionalLight(DirectionalLight* newLight)
{
	directionalLights.push_back(newLight);
}
void RenderingEngine::addPointLight(PointLight* newLight)
{
	pointLights.push_back(newLight);
}
void RenderingEngine::addSpotLight(SpotLight* newLight)
{
	spotLights.push_back(newLight);
}

void RenderingEngine::clearLight()
{
	directionalLights.clear();
	pointLights.clear();
	spotLights.clear();
}