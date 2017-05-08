#ifndef __INPUT_H
#define __INPUT_H

#include <D:/OpenGL2017/SDL2-devel-2.0.5-VC/SDL2-2.0.5/include/SDL.h>

#include "GameObject.h"
#include "Transform.h"
#include "Display.h"

enum InputType
{
	KEY_PRESS_TRANSFORM
};

class Input
{
public:
	Input(int type, GameObject* objectToAffect, int key, Vec9 transform);
	void execute(Display* display);
private:
	int type;
	GameObject* gameObject;
	int key;
	Vec9 transform;

	void keyPressTransform(Display* display);
};

#endif