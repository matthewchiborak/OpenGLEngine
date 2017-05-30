#ifndef __FORWARDDIRECTIONAL_H
#define __FORWARDDIRECTIONAL_H

#include "Shader.h"
#include "RenderingEngine.h"

class ForwardDirectional : public Shader
{
public:
	//ForwardAmbient(const std::string& fileName);
	ForwardDirectional();
	~ForwardDirectional();
	static ForwardDirectional* getForwardDirectional();
	//static void setForwardDirectional(ForwardDirectional* forwardDirectional);

	void update(const Transform& transform, Camera& camera, Transform parentTransform);

private:
	static ForwardDirectional* s_instance;

	enum ForwardDirectionalUniforms
	{
		MODEL,
		MVP,
		SPECULAR_INTENSITY,
		SPECULAR_EXPONENT,
		DIRECTIONAL_LIGHT_BASE_COLOR,
		DIRECTIONAL_LIGHT_BASE_INTENSITY,
		DIRECTIONAL_LIGHT_DIRECTION,
		EYE_POS,
		NUM_UNIFORMS
	};

	GLuint uniforms[ForwardDirectionalUniforms::NUM_UNIFORMS];
};

#endif