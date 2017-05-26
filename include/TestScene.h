#ifndef __TESTSCENE_H
#define __TESTSCENE_H

#include "Scene.h"

//#include "MeshRenderer.h"

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	//Need to inherit
	void init();
	
private:
	/*void update();
	void input(Display* display);
	void render();*/
};

#endif