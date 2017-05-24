#include "../include/RenderingEngine.h"

RenderingEngine* RenderingEngine::s_instance = 0;

RenderingEngine::RenderingEngine()
{
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
	object->render(camera, ShaderManager::getShaderManager()->getShader("Phong"));
}