#ifndef __GAMEOBJECT_H
#define __GAMEOBJECT_H

#include <string>

#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"

class GameObject
{
public:
	GameObject(std::string name, std::string meshFile, Texture* texture, Shader* shader);
	~GameObject();
	void draw(Camera* camera);
	void move(Vec9 change);
	void setTransform(Vec9 change);
	std::string getName();

private:
	std::string name;
	Mesh* mesh;
	Texture* texture;
	Shader* shader;
	Transform transform;
};

#endif