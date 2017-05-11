#ifndef __SHADER_H
#define __SHADER_H

#include <D:/OpenGL2017/glm-0.9.8.4/glm-0.9.8.4/glm/glm.hpp>

#include <string>
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include "Transform.h"
#include "Camera.h"

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

	virtual ~Shader();

private:
	//If using a geometry shader this will be 3. 2 is just vertex and fragment
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other){}

	enum
	{
		TRANSFORM_U,
		BASE_COLOR,
		AMBIENT_LIGHT,

		NUM_UNIFORMS
	};

	//Keeps track of where program is
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];

	glm::fvec3 ambientLight;
	glm::fvec3 baseColor;

};

#endif