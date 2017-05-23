#ifndef __TESTSCENE_H
#define __TESTSCENE_H

#include "Scene.h"

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

	//Need to inherit
	void init();
	
private:
	void earlyUpdate();
	void lateUpdate();
	void input(Display* display);
};

#endif