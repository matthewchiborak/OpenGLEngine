#include "../include/ShaderManager.h"

ShaderManager *ShaderManager::s_instance = 0;

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
	//Delete all the Shaders that were dynamically created in the vector of Shaders
	for (int i = 0; i < shaders.size(); i++)
	{
		delete shaders.at(i);
	}
}

Shader* ShaderManager::getShader(std::string name)
{
	for (int i = 0; i < shaders.size(); i++)
	{
		if (shaders.at(i)->getName() == name)
		{
			return shaders.at(i);
		}
	}

	return NULL;
}

void ShaderManager::loadShader(std::string name, std::string fileName)
{
	shaders.push_back(new Shader(name, fileName));
}

ShaderManager * ShaderManager::getShaderManager()
{
	if (!s_instance)
	{
		s_instance = new ShaderManager();
	}

	return s_instance;
}