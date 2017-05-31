#include "../include/MeshManager.h"

MeshManager *MeshManager::s_instance = 0;

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
	//Delete all the Meshs that were dynamically created in the vector of Meshs
	for (int i = 0; i < meshs.size(); i++)
	{
		delete meshs.at(i);
	}

	if (s_instance)
	{
		delete s_instance;
	}
}

Mesh* MeshManager::getMesh(std::string name)
{
	for (int i = 0; i < meshs.size(); i++)
	{
		if (meshs.at(i)->getName() == name)
		{
			return meshs.at(i);
		}
	}

	return NULL;
}

void MeshManager::loadMesh(std::string name, std::string fileName)
{
	meshs.push_back(new Mesh(name, fileName));
}

MeshManager * MeshManager::getMeshManager()
{
	if (!s_instance)
	{
		s_instance = new MeshManager();
	}

	return s_instance;
}