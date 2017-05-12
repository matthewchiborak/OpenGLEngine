#ifndef __TEXTURE_H
#define __TEXTURE_H

#include <string>
#include <GL/glew.h>
#include "stb_image.h"
#include <cassert>
#include <iostream>

class Texture
{
public:
	Texture(const std::string& fileName);
	Texture(const std::string& name, const std::string& fileName);

	std::string getName();

	//Set opengl to use the texture. Can bind up to 32 textures at once
	void bind(unsigned int unit);

	virtual ~Texture();
private:
	Texture(const Texture& other) {}
	void operator=(const Texture& other) {}

	//Handle to the opengl texture
	GLuint m_texture;

	std::string name;
};

#endif