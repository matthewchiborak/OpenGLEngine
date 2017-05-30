#ifndef __FORWARDSPOT_H
#define __FORWARDSPOT_H

#include "Shader.h"
#include "RenderingEngine.h"

class ForwardSpot : public Shader
{
public:
	//ForwardAmbient(const std::string& fileName);
	ForwardSpot();
	~ForwardSpot();
	static ForwardSpot* getForwardSpot();
	//static void setForwardDirectional(ForwardDirectional* forwardDirectional);

	void update(const Transform& transform, Camera& camera, Transform parentTransform);

private:
	static ForwardSpot* s_instance;

	enum ForwardSpotUniforms
	{
		MODEL,
		MVP,
		SPECULAR_INTENSITY,
		SPECULAR_EXPONENT,
		SPOT_LIGHT_POINT_POSITION,
		SPOT_LIGHT_POINT_COLOR,
		SPOT_LIGHT_POINT_INTENSITY,
		SPOT_LIGHT_POINT_CONSTANT,
		SPOT_LIGHT_POINT_LINEAR,
		SPOT_LIGHT_POINT_EXPONENT,
		SPOT_LIGHT_POINT_RANGE,
		SPOT_LIGHT_DIRECTION,
		SPOT_LIGHT_CUTOFF,
		EYE_POS,
		NUM_UNIFORMS
	};

	GLuint uniforms[ForwardSpotUniforms::NUM_UNIFORMS];
};

#endif