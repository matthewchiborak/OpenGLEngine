#ifndef __RENDERINGENGINE_H
#define __RENDERINGENGINE_H

#include "GameObject.h"
#include "ShaderManager.h"

class RenderingEngine
{
public:
	RenderingEngine();
	~RenderingEngine();

	static RenderingEngine* getRenderingEngine();
	void render(GameObject* object, Camera* camera);

private:
	static RenderingEngine* s_instance;
};

#endif