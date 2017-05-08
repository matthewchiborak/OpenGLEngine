#include "../include/Input.h"

Input::Input(int type, GameObject* objectToAffect, int key, Vec9 transform)
{
	this->type = type;
	gameObject = objectToAffect;
	this->key = key;
	this->transform = transform;
}

void Input::execute(Display* display)
{
	if (type == KEY_PRESS_TRANSFORM)
	{
		keyPressTransform(display);
	}
}

void Input::keyPressTransform(Display* display)
{
	if (display->checkKey(key))
	{
		gameObject->move(transform);
	}
}