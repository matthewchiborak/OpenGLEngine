#ifndef __GAMEOBJECT_H
#define __GAMEOBJECT_H

#include <string>

#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "GameComponent.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "RenderingEngine.h"
#include "PhysicsEngine.h"

class GameComponent;

//Nodes in the scene graph

class GameObject
{
public:
	GameObject(std::string name = "None");
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
	virtual void update(float delta);
	virtual void init();
	virtual void input(float delta);
	void render(Camera* camera);
	//void render(Camera* camera, Shader* shader);
	void render(Camera* camera, Shader* shader, Transform parentTransform);

	void addChild(GameObject* newChild);
	void addComponent(GameComponent* newComponent);

	void addDirectionalLight(DirectionalLight* newLight);
	void addPointLight(PointLight* newLight);
	void addSpotLight(SpotLight* newLight);

	void addToRenderingEngine();

	//For testing purposes
	GameObject* getChild(int index);

	void setPhysicsObject(PhysicsObject* object);
	PhysicsObject* getPhysicsObject();

	void addtoPhysicsEngine(Transform parentTransform);

	void applyPhysicsSimulationChanges();

	void addToHandlePhysicsVector(std::vector<GameObject*>* objectVector);

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

	std::vector<DirectionalLight*> directionalLights;
	std::vector<PointLight*> pointLights;
	std::vector<SpotLight*> spotLights;

	PhysicsObject* physicsObject;
};

#endif