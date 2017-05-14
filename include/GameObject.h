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
	GameObject();
	GameObject(std::string name, std::string meshFile, Texture* texture, Shader* shader);
	GameObject(std::string name, Mesh* mesh, Texture* texture, Shader* shader);
	GameObject(std::string name, Mesh* mesh, Texture* texture, Shader* shader, glm::fvec3 dimensions);
	~GameObject();
	void draw(Camera* camera);
	void move(Vec9 change);
	void setTransform(Vec9 change);
	std::string getName();
	Transform* getTransform();
	virtual void update();
	virtual void init();

	glm::fvec3 getDimensions();

	static GameObject* createSquare(std::string name, float width, float height, float depth, bool oppositeNormal,  float repeatFactorX, float repeatFactorY, Texture* texture, Shader* shader);
	static GameObject* createCube(std::string name, float width, float height, float depth, float repeatFactorX, float repeatFactorY, Texture* texture, Shader* shader);
	static GameObject* createSquarePartTexture(std::string name, float width, float height, float depth, bool oppositeNormal, float XLower, float XHigher, float YLower, float YHigher, Texture* texture, Shader* shader);
	static GameObject* createCubePartTexture(std::string name, float width, float height, float depth, float XLower, float XHigher, float YLower, float YHigher, Texture* texture, Shader* shader);

protected:
	std::string name;
	Mesh* mesh;
	Texture* texture;
	Shader* shader;
	Transform transform;

	glm::fvec3 dimensions;
};

#endif