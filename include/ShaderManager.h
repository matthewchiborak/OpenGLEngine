#ifndef __SHADERMANAGER_H
#define __SHADERMANAGER_H

#include <vector>
#include <string>

#include "Shader.h"

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	Shader* getShader(std::string name);
	void loadShader(std::string name, std::string fileName);

	static ShaderManager* getShaderManager();

private:
	static ShaderManager* s_instance;
	std::vector<Shader*> shaders;
};

#endif