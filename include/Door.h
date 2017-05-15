#ifndef __DOOR_H
#define __DOOR_H

#include "GameObject.h"
#include "Time.h"

class Door : public GameObject
{
public:
	Door(std::string name, float width, float height, float depth, float XLower, float XHigher, float YLower, float YHigher, Texture* texture, Shader* shader);
	~Door();

	//Opens the door allowing the player to move through that tile
	void open();
	void update();

	//Enable ability for door functionallity
	void init();

	const float DOOR_OPEN_RANGE = 1.5;

private:
	bool isOpen;
	bool isOpening;
	//For animating oopening the door
	/*time_t openingStartTime;
	time_t closingStartTime;
	time_t openTime;
	time_t closeTime;
	const double TIME_TO_OPEN = 2;
	const time_t CLOSE_DELAY = 2;*/
	std::chrono::high_resolution_clock::time_point openingStartTime;
	std::chrono::high_resolution_clock::time_point closingStartTime;
	std::chrono::high_resolution_clock::time_point openTime;
	std::chrono::high_resolution_clock::time_point closeTime;
	const int TIME_TO_OPEN = 2000000000;
	const int CLOSE_DELAY = 2000000000; 

	glm::fvec3 openPosition;
	glm::fvec3 closePosition;
};

#endif