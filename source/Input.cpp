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
Input::Input(int type, Camera* objectToAffect, int key, float magnitude)
{
	this->type = type;
	gameObject = NULL;
	this->key = key;
	this->magnitude = magnitude;
	cameraObject = objectToAffect;
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
	else if (type == KEY_PRESS_FORWARD_CAMERA_TRANSFORM)
	{
		keyPressForwardTransform(display);
	}
	else if (type == KEY_PRESS_LEFT_CAMERA_TRANSFORM)
	{
		keyPressLeftTransform(display);
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
	cameraObject->rotateX(cameraObject->getSensitivity() * display->getMouseDifY());
}

void Input::keyPressForwardTransform(Display* display)
{
	if (display->checkKey(key))
	{
		glm::vec3 temp(cameraObject->getForward().x * magnitude, cameraObject->getForward().y * magnitude, cameraObject->getForward().z * magnitude);

		cameraObject->movePosition(temp);
	}
}
void Input::keyPressLeftTransform(Display* display)
{
	if (display->checkKey(key))
	{
		glm::vec3 left = glm::cross(cameraObject->getForward(), cameraObject->getUp());

		glm::vec3 temp(left.x * magnitude, left.y * magnitude, left.z * magnitude);

		cameraObject->movePosition(temp);
	}
}