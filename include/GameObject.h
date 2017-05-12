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
	GameObject(std::string name, Mesh* mesh, Texture* texture, Shader* shader);
	~GameObject();
	void draw(Camera* camera);
	void move(Vec9 change);
	void setTransform(Vec9 change);
	std::string getName();

	static GameObject* createSquare(std::string name, float width, float height, float depth, bool oppositeNormal,  float repeatFactorX, float repeatFactorY, Texture* texture, Shader* shader);
	static GameObject* createCube(std::string name, float width, float height, float depth, float repeatFactorX, float repeatFactorY, Texture* texture, Shader* shader);

private:
	std::string name;
	Mesh* mesh;
	Texture* texture;
	Shader* shader;
	Transform transform;
};

#endif