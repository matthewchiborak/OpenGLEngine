#ifndef __SHADER_H
#define __SHADER_H

#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/glm.hpp>

#include <string>
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include "Transform.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"

class Shader
{
public:
	Shader(const std::string& fileName);

	//Set cpu to use shader
	void bind();

	void update(const Transform& transform, Camera& camera);

	void setAmbientLight(glm::fvec3 light);
	glm::fvec3 getAmbientLight();
	void setBaseColor(glm::fvec3 color);
	glm::fvec3 getBaseColor();

	void setDirectionalBase(glm::fvec3 color, float intensity);
	void setDirectionalDirection(glm::fvec3 direction);

	void setSpecularIntensity(float value);
	void setSpecularExponent(float value);

	static void setPointLight(int index, glm::fvec3 position, glm::fvec3 color, float intensity, float constant, float linear, float exponent);

	virtual ~Shader();

private:
	//If using a geometry shader this will be 3. 2 is just vertex and fragment
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other){}

	enum
	{
		TRANSFORM_U,
		TRANSFORM_PROJECTED,
		BASE_COLOR,
		AMBIENT_LIGHT,
		DIRECTIONAL_LIGHT_BASE_COLOR,
		DIRECTIONAL_LIGHT_BASE_INTENSITY,
		DIRECTIONAL_LIGHT_DIRECTION,

		SPECULAR_INTENSITY,
		SPECULAR_EXPONENT,
		EYE_POS,

		POINT_LIGHT_POSITION0,
		POINT_LIGHT_BASE_COLOR0,
		POINT_LIGHT_BASE_INTENSITY0,
		POINT_LIGHT_ATTEN_CONSTANT0,
		POINT_LIGHT_ATTEN_LINEAR0,
		POINT_LIGHT_ATTEN_EXPONENT0,

		POINT_LIGHT_POSITION1,
		POINT_LIGHT_BASE_COLOR1,
		POINT_LIGHT_BASE_INTENSITY1,
		POINT_LIGHT_ATTEN_CONSTANT1,
		POINT_LIGHT_ATTEN_LINEAR1,
		POINT_LIGHT_ATTEN_EXPONENT1,

		POINT_LIGHT_POSITION2,
		POINT_LIGHT_BASE_COLOR2,
		POINT_LIGHT_BASE_INTENSITY2,
		POINT_LIGHT_ATTEN_CONSTANT2,
		POINT_LIGHT_ATTEN_LINEAR2,
		POINT_LIGHT_ATTEN_EXPONENT2,

		POINT_LIGHT_POSITION3,
		POINT_LIGHT_BASE_COLOR3,
		POINT_LIGHT_BASE_INTENSITY3,
		POINT_LIGHT_ATTEN_CONSTANT3,
		POINT_LIGHT_ATTEN_LINEAR3,
		POINT_LIGHT_ATTEN_EXPONENT3,

		NUM_UNIFORMS
	};

	//Keeps track of where program is
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];

	//MUST BE THE SAME AS IT IS IN THE SHADER glsl. 
	static const int MAX_POINT_LIGHTS = 4;
	static PointLight pointLights[MAX_POINT_LIGHTS];
	GLuint m_pointLight_uniforms[MAX_POINT_LIGHTS * 5];

	glm::fvec3 ambientLight;
	glm::fvec3 baseColor;

	DirectionalLight directionalLight;

	float specularIntensity;
	//This is how wide the reflection is
	float specularExponent;
};

#endif