#ifndef __MEDKIT_H
#define __MEDKIT_H

#include "GameObject.h"
#include "Scene.h"

class Scene;

class Medkit : public GameObject
{
public:
	Medkit(std::string name, float width, float height, float depth, float XLower, float XHigher, float YLower, float YHigher, Texture* texture, Shader* shader, Camera* camera, Scene* myScene);
	~Medkit();
	void update();

	//Enable ability for monster functionallity
	void init();

	static float SIZEX;
	static float SIZEY;
	static int healAmount;

private:
	Camera* camera;
	Scene* myScene;
};

#endif