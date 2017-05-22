#ifndef __TESTSCENE_H
#define __TESTSCENE_H

#include "Scene.h"
#include "Door.h"
#include "Monster.h"
#include "Medkit.h"
#include "Bitmap.h"

//#include <D:/OpenGL2017/SDL2-devel-2.0.5-VC/SDL2-2.0.5/include/SDL.h>

class Door;
class Monster;
class Medkit;

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	//Need to inherit
	void update();
	void lateUpdate();
	void init();
	void input(Display* display);

	bool isAtExit();
	glm::fvec3 checkCollisionEnemyWalls(Monster* monster, glm::fvec3 movement, float objectWidth, float objectHeight, float objectDepth);
	bool checkIntersection(glm::fvec2* result, glm::fvec2 lineStart, glm::fvec2 lineEnd, bool hurtMonsters);
	std::vector<Door*>* getDoors();
	std::vector<Monster*>* getMonsters();
	glm::fvec3 checkCollisionCameraWalls(Camera* camera, glm::fvec3 movement, float objectWidth, float objectHeight, float objectDepth);
private:
	
	std::vector<glm::vec2*> exits;
	GameObject* HUD;
	std::vector<Door*> doors;
	std::vector<Monster*> monsters;
	std::vector<Medkit*> medkits;
	Bitmap* level;
	const float DOOR_THICKNESS = 0.125f;
	std::vector<glm::fvec2*> collisionPosStart;
	std::vector<glm::fvec2*> collisionPosEnd;

	void generateLevel(std::string fileName);

	void addSpecial(int blueValue, int x, int z);
};

#endif