#include "../include/Input.h"

Input::Input(int type, GameObject* objectToAffect, int key, Vec9 transform)
{
	this->type = type;
	gameObject = objectToAffect;
	this->key = key;
	this->transform = transform;
	cameraObject = NULL;
}
Input::Input(int type, Camera* objectToAffect, int key, Vec9 transform)
{
	this->type = type;
	cameraObject = objectToAffect;
	this->key = key;
	this->transform = transform;
	gameObject = NULL;
}
Input::Input(int type, Camera* objectToAffect)
{
	this->type = type;
	cameraObject = objectToAffect;
	this->key = NULL;
	gameObject = NULL;
}

void Input::execute(Display* display)
{
	if (type == KEY_PRESS_TRANSFORM)
	{
		keyPressTransform(display);
	}
	else if (type == KEY_PRESS_DOWN_TRANSFORM)
	{
		keyPressDownTransform(display);
	}
	else if (type == KEY_PRESS_UP_TRANSFORM)
	{
		keyPressUpTransform(display);
	}
	else if (type == KEY_PRESS_CAMERA_TRANSFORM)
	{
		keyPressCameraTransform(display);
	}
	else if (type == KEY_PRESS_DOWN_CAMERA_TRANSFORM)
	{
		keyPressDownCameraTransform(display);
	}
	else if (type == KEY_PRESS_UP_CAMERA_TRANSFORM)
	{
		keyPressUpCameraTransform(display);
	}
	else if (type == MOUSE_MOVE_X_TRANSFORM)
	{
		mouseMoveXTransform(display);
	}
	else if (type == MOUSE_MOVE_Y_TRANSFORM)
	{
		mouseMoveYTransform(display);
	}
}

void Input::keyPressTransform(Display* display)
{
	if (display->checkKey(key))
	{
		gameObject->move(transform);
	}
}
void Input::keyPressDownTransform(Display* display)
{
	if (display->checkKeyDown(key))
	{
		gameObject->move(transform);
	}
}
void Input::keyPressUpTransform(Display* display)
{
	if (display->checkKeyUp(key))
	{
		gameObject->move(transform);
	}
}
void Input::keyPressCameraTransform(Display* display)
{
	if (display->checkKey(key))
	{
		cameraObject->movePosition(transform.pos);
		//cameraObject->moveForward(transform.pos);
	}
}
void Input::keyPressDownCameraTransform(Display* display)
{
	if (display->checkKeyDown(key))
	{
		cameraObject->movePosition(transform.pos);
		//cameraObject->moveForward(transform.pos);
	}
}
void Input::keyPressUpCameraTransform(Display* display)
{
	if (display->checkKeyUp(key))
	{
		cameraObject->movePosition(transform.pos);
		//cameraObject->moveForward(transform.pos);
	}
}

void Input::mouseMoveXTransform(Display* display)
{
	/*cameraObject->movePosition(glm::vec3(sin(cameraObject->getSensitivity() * display->getMouseDifX()) * (cameraObject->getForward().x - cameraObject->getPosition().x),
		0,
		cos(cameraObject->getSensitivity() * display->getMouseDifX()) * (cameraObject->getForward().z - cameraObject->getPosition().z)));*/

	/*cameraObject->moveForward(glm::vec3(sin(cameraObject->getSensitivity() * display->getMouseDifX()) * (cameraObject->getForward().x - cameraObject->getPosition().x), 
		0, 
		cos(cameraObject->getSensitivity() * display->getMouseDifX()) * (cameraObject->getForward().z - cameraObject->getPosition().z)));*/

	cameraObject->rotateY(cameraObject->getSensitivity() * display->getMouseDifX());
}
void Input::mouseMoveYTransform(Display* display)
{
	//cameraObject->moveForward();
}