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
	cameraObject->rotateY(cameraObject->getSensitivity() * display->getMouseDifX());
}
void Input::mouseMoveYTransform(Display* display)
{
	cameraObject->rotateX(cameraObject->getSensitivity() * display->getMouseDifY());
}

void Input::keyPressForwardTransform(Display* display)
{
	if (display->checkKey(key))
	{
		glm::fvec3 movementAmount(cameraObject->getForward().x * magnitude, cameraObject->getForward().y * magnitude, cameraObject->getForward().z * magnitude);
		//glm::fvec3 collisionResult = myScene->checkCollisionCamera(cameraObject, movementAmount, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE);
		glm::fvec3 collisionResult = myScene->checkCollisionCameraWalls(cameraObject, movementAmount, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE);

		
		movementAmount.x *= collisionResult.x;
		movementAmount.y *= collisionResult.y;
		movementAmount.z *= collisionResult.z;

		cameraObject->movePosition(movementAmount);
	}
}
void Input::keyPressLeftTransform(Display* display)
{
	if (display->checkKey(key))
	{
		glm::vec3 left = glm::cross(cameraObject->getForward(), cameraObject->getUp());

		glm::fvec3 movementAmount(left.x * magnitude, left.y * magnitude, left.z * magnitude);

		//glm::fvec3 collisionResult = myScene->checkCollisionCamera(cameraObject, movementAmount, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE);
		glm::fvec3 collisionResult = myScene->checkCollisionCameraWalls(cameraObject, movementAmount, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE, Scene::PLAYER_SIZE);

		movementAmount.x *= collisionResult.x;
		movementAmount.y *= collisionResult.y;
		movementAmount.z *= collisionResult.z;

		cameraObject->movePosition(movementAmount);
	}
}

void Input::assignScene(Scene* myScene)
{
	this->myScene = myScene;
}