#include <iostream>
#include <GL/glew.h>
#include <D:/OpenGL2017/SDL2-devel-2.0.5-VC/SDL2-2.0.5/include/SDL.h>

#include "../include/Display.h"
#include "../include/Shader.h"
#include "../include/Mesh.h"
#include "../include/Texture.h"
#include "../include/Transform.h"
#include "../include/Camera.h"
#include "../include/Time.h"
#include "../include/GameObject.h"
#include "../include/Input.h"
#include "../include/Scene.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv)
{
	Display display(WIDTH, HEIGHT, "Hello world!");

	int currentScene = 0;
	std::vector<Scene*> scenes;
	scenes.push_back(new Scene("Main", WIDTH, HEIGHT));

	//scenes.at(currentScene)->resetCamera(Vec9::createVec9(0, 1, -2, 0, 0, 1, 0, 1, 0));

	//Shader shader(".\\res\\basicShader");
	Shader shader(".\\res\\PhongShader");
	shader.setAmbientLight(glm::fvec3(0.1f,0.1f,0.1f));
	shader.setBaseColor(glm::fvec3(1.0f, 1.0f, 1.0f));
	shader.setDirectionalDirection(glm::fvec3(1, 0.2, 0));
	shader.setDirectionalBase(glm::fvec3(1, 1, 1), 1);
	shader.setSpecularIntensity(2);
	shader.setSpecularExponent(32);

	Texture wall(".\\res\\bricks.jpg");
	Texture texture(".\\res\\body.png");
	Texture floor(".\\res\\floor.jpg");
	//Texture ceiling(".\\res\\ceiling.jpg");
	
	//scenes.at(currentScene)->addGameObjectToScene(new GameObject("Ship", "./res/arwing.obj", &texture, &shader));
	//scenes.at(currentScene)->addGameObjectToScene(new GameObject("Monkey", "./res/monkey3.obj", &texture2, &shader));

	scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("TestCube", 5, 10, 5, 0.5, 0.5, &wall, &shader));
	scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("TestCube2", 5, 10, 5, 1, 1, &wall, &shader));
	scenes.at(currentScene)->getGameObject("TestCube2")->move(Vec9::createVec9(Direction::MOVE_X, 10));

	scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("Floor", 25, 1, 25, 0.5, 0.5, &floor, &shader));
	scenes.at(currentScene)->getGameObject("Floor")->move(Vec9::createVec9(Direction::MOVE_Y, -5));
	scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("Ceiling", 25, 1, 25, 0.5, 0.5, &texture, &shader));
	scenes.at(currentScene)->getGameObject("Ceiling")->move(Vec9::createVec9(Direction::MOVE_Y, 5));

	scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("Wall1", 1, 10, 25, 0.5, 0.5, &wall, &shader));
	scenes.at(currentScene)->getGameObject("Wall1")->move(Vec9::createVec9(Direction::MOVE_X, 12.5));
	scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("Wall2", 1, 10, 25, 0.5, 0.5, &wall, &shader));
	scenes.at(currentScene)->getGameObject("Wall2")->move(Vec9::createVec9(Direction::MOVE_X, -12.5));
	scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("Wall3", 25, 10, 1, 0.5, 0.5, &wall, &shader));
	scenes.at(currentScene)->getGameObject("Wall3")->move(Vec9::createVec9(Direction::MOVE_Z, 12.5));
	scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("Wall4", 25, 10, 1, 0.5, 0.5, &wall, &shader));
	scenes.at(currentScene)->getGameObject("Wall4")->move(Vec9::createVec9(Direction::MOVE_Z, -12.5));

	//Assign inputs to the gameobject
	/*scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_TRANSFORM, scenes.at(currentScene)->getGameObject("Arwing"), SDLK_w, Vec9::createVec9(Direction::MOVE_Y, 0.01)));
	scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_TRANSFORM, scenes.at(currentScene)->getGameObject("Arwing"), SDLK_a, Vec9::createVec9(Direction::MOVE_X, 0.01)));
	scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_TRANSFORM, scenes.at(currentScene)->getGameObject("Arwing"), SDLK_s, Vec9::createVec9(Direction::MOVE_Y, -0.01)));
	scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_TRANSFORM, scenes.at(currentScene)->getGameObject("Arwing"), SDLK_d, Vec9::createVec9(Direction::MOVE_X, -0.01)));

	scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_TRANSFORM, scenes.at(currentScene)->getGameObject("Arwing"), SDLK_q, Vec9::createVec9(Direction::ROT_Y, 0.01)));
	scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_TRANSFORM, scenes.at(currentScene)->getGameObject("Arwing"), SDLK_e, Vec9::createVec9(Direction::ROT_Y, -0.01)));

	scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_TRANSFORM, scenes.at(currentScene)->getGameObject("Monkey"), SDLK_e, Vec9::createVec9(Direction::ROT_Y, -0.01)));
	scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_TRANSFORM, scenes.at(currentScene)->getGameObject("Monkey"), SDLK_r, Vec9::createVec9(Direction::MOVE_Y, 0.01)));*/
	//scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_UP_TRANSFORM, scenes.at(currentScene)->getGameObject("Arwing"), SDLK_w, Vec9::createVec9(Direction::MOVE_Y, 1)));
	//scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_UP_TRANSFORM, scenes.at(currentScene)->getGameObject("Arwing"), SDLK_s, Vec9::createVec9(Direction::MOVE_Y, -1)));
	//scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_CAMERA_TRANSFORM, scenes.at(currentScene)->getCamera(), SDLK_w, Vec9::createVec9(Direction::MOVE_Z, 0.1)));
	//scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_CAMERA_TRANSFORM, scenes.at(currentScene)->getCamera(), SDLK_s, Vec9::createVec9(Direction::MOVE_Z, -0.1)));
	scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_FORWARD_CAMERA_TRANSFORM, scenes.at(currentScene)->getCamera(), SDLK_w, 0.1));
	scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_FORWARD_CAMERA_TRANSFORM, scenes.at(currentScene)->getCamera(), SDLK_s, -0.1));
	scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_LEFT_CAMERA_TRANSFORM, scenes.at(currentScene)->getCamera(), SDLK_d, 0.1));
	scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_LEFT_CAMERA_TRANSFORM, scenes.at(currentScene)->getCamera(), SDLK_a, -0.1));
	//scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_CAMERA_TRANSFORM, scenes.at(currentScene)->getCamera(), SDLK_s, Vec9::createVec9(Direction::MOVE_Z, -0.1)));
	//scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_CAMERA_TRANSFORM, scenes.at(currentScene)->getCamera(), SDLK_s, Vec9::createVec9(Direction::MOVE_Z, -0.1)));
	//scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_CAMERA_TRANSFORM, scenes.at(currentScene)->getCamera(), SDLK_a, Vec9::createVec9(Direction::MOVE_X, 0.1)));
	//scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_CAMERA_TRANSFORM, scenes.at(currentScene)->getCamera(), SDLK_d, Vec9::createVec9(Direction::MOVE_X, -0.1)));
	scenes.at(currentScene)->addInputToScene(new Input(MOUSE_MOVE_X_TRANSFORM, scenes.at(currentScene)->getCamera()));
	//scenes.at(currentScene)->addInputToScene(new Input(MOUSE_MOVE_Y_TRANSFORM, scenes.at(currentScene)->getCamera()));
	scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_CAMERA_TRANSFORM, scenes.at(currentScene)->getCamera(), SDLK_q, Vec9::createVec9(Direction::MOVE_Y, 0.1)));
	scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_CAMERA_TRANSFORM, scenes.at(currentScene)->getCamera(), SDLK_e, Vec9::createVec9(Direction::MOVE_Y, -0.1)));

	scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_TRANSFORM, scenes.at(currentScene)->getGameObject("TestCube"), SDLK_f, Vec9::createVec9(Direction::ROT_Y, -0.01)));

	

	float counter = 0.0f;

	//Event for input
	SDL_Event event;

	//Fixed frame rate
	static double FRAME_CAP = 5000.0;
	long lastTime = Time::getTime();
	double unprocessedTime = 0; //Keep track of time still needed to be processed to update the game
	double frameTime = 1.0 / FRAME_CAP;
	int frames = 0;
	long frameCounter = 0;
	
	while (!display.isClosed())
	{
		//Fixed Frame rate
		long startTime = Time::getTime();
		long passedTime = startTime - lastTime;
		lastTime = startTime;
		frameCounter += passedTime;
		//Time::setDelta(frameTime);

		//UPDATE GAME
		display.clear(0.0f, 0.15f, 0.3f, 1.0f);

		scenes.at(currentScene)->update(&display);
		display.Update();

		counter += 0.01f;
		frames++;

		//Output the framerate
		if (frameCounter >= Time::SECOND)
		{
			std::cout << "FPS: " << frames << "\n";
			frames = 0;
			frameCounter = 0;
		}
	}

	////Delete the scenes
	for (int i = 0; i < scenes.size(); i++)
	{
		if (scenes.at(i) != NULL)
		{
			delete scenes.at(i);
		}
	}

	return 0;
}