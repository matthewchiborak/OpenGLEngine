#ifndef __INPUT_H
#define __INPUT_H

#include <D:/OpenGL2017/SDL2-devel-2.0.5-VC/SDL2-2.0.5/include/SDL.h>

#include "GameObject.h"
#include "Transform.h"
#include "Display.h"
#include "Camera.h"

enum InputType
{
	KEY_PRESS_TRANSFORM,
	KEY_PRESS_DOWN_TRANSFORM,
	KEY_PRESS_UP_TRANSFORM,
	KEY_PRESS_CAMERA_TRANSFORM,
	KEY_PRESS_DOWN_CAMERA_TRANSFORM,
	KEY_PRESS_UP_CAMERA_TRANSFORM,

	MOUSE_MOVE_X_TRANSFORM,
	MOUSE_MOVE_Y_TRANSFORM,

	KEY_PRESS_FORWARD_CAMERA_TRANSFORM,
	KEY_PRESS_LEFT_CAMERA_TRANSFORM
};

class Input
{
public:
	Input(int type, GameObject* objectToAffect, int key, Vec9 transform);
	Input(int type, Camera* objectToAffect, int key, Vec9 transform);
	Input(int type, Camera* objectToAffect, int key, float magnitude);
	Input(int type, Camera* objectToAffect);
	void execute(Display* display);
private:
	int type;
	GameObject* gameObject;
	Camera* cameraObject;
	int key;
	Vec9 transform;
	float magnitude;

	void keyPressTransform(Display* display);
	void keyPressDownTransform(Display* display);
	void keyPressUpTransform(Display* display);
	void keyPressCameraTransform(Display* display);
	void keyPressDownCameraTransform(Display* display);
	void keyPressUpCameraTransform(Display* display);
	void mouseMoveXTransform(Display* display);
	void mouseMoveYTransform(Display* display);

	void keyPressForwardTransform(Display* display);
	void keyPressLeftTransform(Display* display);
};

#endif