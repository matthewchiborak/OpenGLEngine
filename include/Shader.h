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

class Shader
{
public:
	Shader(const std::string& fileName);

	//Set cpu to use shader
	void bind();

	void update(const Transform& transform, const Camera& camera);

	void setAmbientLight(glm::fvec3 light);
	glm::fvec3 getAmbientLight();
	void setBaseColor(glm::fvec3 color);
	glm::fvec3 getBaseColor();

	void setDirectionalBase(glm::fvec3 color, float intensity);
	void setDirectionalDirection(glm::fvec3 direction);

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

		NUM_UNIFORMS
	};

	//Keeps track of where program is
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];

	glm::fvec3 ambientLight;
	glm::fvec3 baseColor;

	DirectionalLight directionalLight;
};

#endif