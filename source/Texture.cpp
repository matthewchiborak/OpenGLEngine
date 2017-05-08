#include "../include/Texture.h"

Texture::Texture(const std::string& fileName)
{
	//Depends on the texture loader

	//Returned info on the image
	//unsigned int width, height, numComponents;
	int width, height, numComponents;

	//Load texture data
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
	{
		std::cerr << "Texture loading failed for texture: " << fileName << "\n";
	}

	//Generate space for the data in opengl
	//This is generate space for 1 texture
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	//Before specify texture data, can specify other things
	//These control texture wrapping. S is reading outside texture width, t is for height.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//If texture takes up more or less space than specified. 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //Fewer pixels than resolution
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //More

	//Send in data. Mitmapping using heigher resolution images the closer it is. But here its 0 so just use dfault
	//
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	//Free the texture data once no longer needed
	stbi_image_free(imageData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::bind(unsigned int unit)
{
	//Opengl range is 0-31
	assert(unit >= 0 && unit <= 31);

	//Change what texture the program with working with
	//GL_TEXTURE unit is ordered sequentialy so can jsut add it
	glActiveTexture(GL_TEXTURE0 + unit);

	//All future texture operations will use the texture that is stored there.
	glBindTexture(GL_TEXTURE_2D, m_texture);
}