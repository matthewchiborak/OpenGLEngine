#ifndef __RENDERINGENGINE_H
#define __RENDERINGENGINE_H

#include "GameObject.h"
#include "ShaderManager.h"
#include "ForwardAmbient.h"

class RenderingEngine
{
public:
	RenderingEngine();
	~RenderingEngine();

	static RenderingEngine* getRenderingEngine();
	void render(GameObject* object, Camera* camera);

	glm::fvec3 getAmbientLight();

private:
	static RenderingEngine* s_instance;

	//Forward rendering lighting
	glm::fvec3 ambientLight;
};

#endif