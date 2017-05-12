#include "../include/TextureManager.h"

TextureManager *TextureManager::s_instance = 0;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	//Delete all the textures that were dynamically created in the vector of textures
	for (int i = 0; i < textures.size(); i++)
	{
		delete textures.at(i);
	}
}

Texture* TextureManager::getTexture(std::string name)
{
	for (int i = 0; i < textures.size(); i++)
	{
		if (textures.at(i)->getName() == name)
		{
			return textures.at(i);
		}
	}

	return NULL;
}

void TextureManager::loadTexture(std::string name, std::string fileName)
{
	textures.push_back(new Texture(name, fileName));
}

TextureManager * TextureManager::getTextureManager()
{
	if (!s_instance)
	{
		s_instance = new TextureManager();
	}

	return s_instance;
}