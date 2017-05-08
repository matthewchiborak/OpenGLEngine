#ifndef __SHADER_H
#define __SHADER_H

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

	virtual ~Shader();

private:
	//If using a geometry shader this will be 3. 2 is just vertex and fragment
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator=(const Shader& other){}

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	//Keeps track of where program is
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif