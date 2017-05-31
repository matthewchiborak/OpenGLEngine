#ifndef __MESHMANAGER_H
#define __MESHMANAGER_H

#include <vector>
#include <string>

#include "Mesh.h"

class MeshManager
{
public:
	MeshManager();
	~MeshManager();

	Mesh* getMesh(std::string name);
	void loadMesh(std::string name, std::string fileName);

	static MeshManager* getMeshManager();

private:
	static MeshManager* s_instance;
	std::vector<Mesh*> meshs;
};

#endif