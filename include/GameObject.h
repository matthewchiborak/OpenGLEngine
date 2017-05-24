#ifndef __GAMEOBJECT_H
#define __GAMEOBJECT_H

#include <string>

#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "GameComponent.h"

class GameComponent;

//Nodes in the scene graph

class GameObject
{
public:
	GameObject();
	GameObject(std::string name, std::string meshFile, Texture* texture, Shader* shader);
	GameObject(std::string name, Mesh* mesh, Texture* texture, Shader* shader);
	GameObject(std::string name, Mesh* mesh, Texture* texture, Shader* shader, glm::fvec3 dimensions);
	~GameObject();
	//void draw(Camera* camera);
	void move(Vec9 change);
	void setTransform(Vec9 change);
	std::string getName();
	Transform* getTransform();


	glm::fvec3 getDimensions();

	bool isEnabled();

	static GameObject* createSquare(std::string name, float width, float height, float depth, bool oppositeNormal,  float repeatFactorX, float repeatFactorY, Texture* texture, Shader* shader);
	static GameObject* createCube(std::string name, float width, float height, float depth, float repeatFactorX, float repeatFactorY, Texture* texture, Shader* shader);
	static GameObject* createSquarePartTexture(std::string name, float width, float height, float depth, bool oppositeNormal, float XLower, float XHigher, float YLower, float YHigher, Texture* texture, Shader* shader);
	static GameObject* createCubePartTexture(std::string name, float width, float height, float depth, float XLower, float XHigher, float YLower, float YHigher, Texture* texture, Shader* shader);

	//Switching to scene graph. Unsure if this is how I want to do it
	virtual void update();
	virtual void init();
	virtual void input();
	void render(Camera* camera);

	void addChild(GameObject* newChild);
	void addComponent(GameComponent* newComponent);

protected:
	std::string name;
	//Mesh* mesh;
	Texture* texture;
	Shader* shader;
	Transform transform;

	glm::fvec3 dimensions;
	bool enabled;

	//Node properties
	//All children inherit properties of above
	std::vector<GameObject*> children;
	std::vector<GameComponent*> components;
};

#endif