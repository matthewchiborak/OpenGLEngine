#ifndef __TEXTUREMANAGER_H
#define __TEXTUREMANAGER_H

#include <vector>
#include <string>

#include "Texture.h"

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	Texture* getTexture(std::string name);
	void loadTexture(std::string name, std::string fileName);

	static TextureManager* getTextureManager();

private:
	static TextureManager* s_instance;
	std::vector<Texture*> textures;
};

#endif