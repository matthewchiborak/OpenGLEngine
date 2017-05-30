#ifndef __FORWARDPOINT_H
#define __FORWARDPOINT_H

#include "Shader.h"
#include "RenderingEngine.h"

class ForwardPoint : public Shader
{
public:
	//ForwardAmbient(const std::string& fileName);
	ForwardPoint();
	~ForwardPoint();
	static ForwardPoint* getForwardPoint();
	//static void setForwardDirectional(ForwardDirectional* forwardDirectional);

	void update(const Transform& transform, Camera& camera, Transform parentTransform);

private:
	static ForwardPoint* s_instance;

	enum ForwardPointUniforms
	{
		MODEL,
		MVP,
		SPECULAR_INTENSITY,
		SPECULAR_EXPONENT,
		POINT_LIGHT_POSITION,
		POINT_LIGHT_BASE_COLOR,
		POINT_LIGHT_BASE_INTENSITY,
		POINT_LIGHT_ATTEN_CONSTANT,
		POINT_LIGHT_ATTEN_LINEAR,
		POINT_LIGHT_ATTEN_EXPONENT,
		POINT_LIGHT_RANGE,
		EYE_POS,
		NUM_UNIFORMS
	};

	GLuint uniforms[ForwardPointUniforms::NUM_UNIFORMS];
};

#endif