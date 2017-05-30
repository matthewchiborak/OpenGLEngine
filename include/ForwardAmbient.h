#ifndef __FORWARDAMBIENT_H
#define __FORWARDAMBIENT_H

#include "Shader.h"
#include "RenderingEngine.h"

class ForwardAmbient : public Shader
{
public:
	//ForwardAmbient(const std::string& fileName);
	ForwardAmbient();
	~ForwardAmbient();
	static ForwardAmbient* getForwardAmbient();

	void update(const Transform& transform, Camera& camera, Transform parentTransform);

private:
	static ForwardAmbient* s_instance;

	enum ForwardAmbientUniforms
	{
		MVP,
		AMBIENT_INTENSITY,
		NUM_UNIFORMS
	};

	GLuint uniforms[ForwardAmbientUniforms::NUM_UNIFORMS];
};

#endif