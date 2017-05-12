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
#include "../include/Bitmap.h"

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
	shader.setDirectionalDirection(glm::fvec3(0, 1, 0));
	shader.setDirectionalBase(glm::fvec3(0, 0, 0), 0);
	//Note to self. Having directional color to white but intensity to 0 causes the specular reflection to give a flashlight effect

	shader.setSpecularIntensity(2);
	shader.setSpecularExponent(32);

	/*shader.setPointLight(0, glm::fvec3(-2, 0, 6), glm::fvec3(1, 0, 0), 10.0f, 0, 0, 1);
	shader.setPointLight(1, glm::fvec3(2, 0, 7), glm::fvec3(0,0, 1), 10, 0, 0, 1);*/
	shader.setPointLight(0, glm::fvec3(-2, 0, 6), glm::fvec3(1, 1, 1), 10.0f, 20, 0, 0, 1);
	//shader.setPointLight(1, glm::fvec3(2, 0, 7), glm::fvec3(1, 1, 1), 10, 20, 0, 0, 1);

	//shader.setSpotLight(0, glm::fvec3(-2, 0, 6), glm::fvec3(1, 1, 1), 0.4f, 20, 0, 0, 0.02f, glm::vec3(0, 0, 1), 0.7);

	Texture wall(".\\res\\bricks.jpg");
	Texture texture(".\\res\\body.png");
	Texture floor(".\\res\\floor.jpg");
	//Texture ceiling(".\\res\\ceiling.jpg");

	//Wolf3d////////////////////////////////////
	//Build the level
	Bitmap level(".\\res\\Level1.png");
	level.flipX();
	level.flipY();

	const float SPOT_WIDTH = 1;
	const float SPOT_HEIGHT = 1;
	const float SPOT_DEPTH = 1;

	for (int i = 0; i < level.getWidth(); i++)
	{
		for (int j = 0; j < level.getHeight(); j++)
		{
			if (level.getPixel(i, j).r == 0 && level.getPixel(i, j).g == 0 && level.getPixel(i, j).b == 0)
			{
				//Its a wall
				continue;
			}

			//Floor
			scenes.at(currentScene)->addGameObjectToScene(GameObject::createSquare("Wolf3DFloor_" + std::to_string(i) + "_" + std::to_string(j), SPOT_WIDTH, 0, SPOT_DEPTH, false, 1, 1, &floor, &shader));
			scenes.at(currentScene)->getGameObject("Wolf3DFloor_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9(i * SPOT_WIDTH, 0, j * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));

			//Ceiling
			scenes.at(currentScene)->addGameObjectToScene(GameObject::createSquare("Wolf3DCeiling_" + std::to_string(i) + "_" + std::to_string(j), SPOT_WIDTH, 0, SPOT_DEPTH, true, 1, 1, &floor, &shader));
			scenes.at(currentScene)->getGameObject("Wolf3DCeiling_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9(i * SPOT_WIDTH, SPOT_HEIGHT, j * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));

			//walls. Check if ajacent is a wall
			/*if (level.getPixel(i, j - 1).r == 0 && level.getPixel(i, j - 1).g == 0 && level.getPixel(i, j - 1).b == 0)
			{
				scenes.at(currentScene)->addGameObjectToScene(GameObject::createSquare("Wolf3DWall_a_" + std::to_string(i) + "_" + std::to_string(j), SPOT_WIDTH, SPOT_HEIGHT, 0, false, 1, 1, &wall, &shader));
				scenes.at(currentScene)->getGameObject("Wolf3DWall_a_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9(i * SPOT_WIDTH, SPOT_HEIGHT / 2, (j - 0.5) * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
			}
			if (level.getPixel(i, j + 1).r == 0 && level.getPixel(i, j + 1).g == 0 && level.getPixel(i, j + 1).b == 0)
			{
				scenes.at(currentScene)->addGameObjectToScene(GameObject::createSquare("Wolf3DWall_b_" + std::to_string(i) + "_" + std::to_string(j), SPOT_WIDTH, SPOT_HEIGHT, 0, true, 1, 1, &wall, &shader));
				scenes.at(currentScene)->getGameObject("Wolf3DWall_b_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9(i * SPOT_WIDTH, SPOT_HEIGHT / 2, (j + 0.5) * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
			}
			if (level.getPixel(i - 1, j).r == 0 && level.getPixel(i - 1, j).g == 0 && level.getPixel(i - 1, j).b == 0)
			{
				scenes.at(currentScene)->addGameObjectToScene(GameObject::createSquare("Wolf3DWall_c_" + std::to_string(i) + "_" + std::to_string(j), 0, SPOT_HEIGHT, SPOT_DEPTH, false, 1, 1, &wall, &shader));
				scenes.at(currentScene)->getGameObject("Wolf3DWall_c_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9((i - 0.5) * SPOT_WIDTH, SPOT_HEIGHT / 2, (j)* SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
			}
			if (level.getPixel(i + 1, j).r == 0 && level.getPixel(i + 1, j).g == 0 && level.getPixel(i + 1, j).b == 0)
			{
				scenes.at(currentScene)->addGameObjectToScene(GameObject::createSquare("Wolf3DWall_d_" + std::to_string(i) + "_" + std::to_string(j), 0, SPOT_HEIGHT, SPOT_DEPTH, true, 1, 1, &wall, &shader));
				scenes.at(currentScene)->getGameObject("Wolf3DWall_d_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9((i + 0.5) * SPOT_WIDTH, SPOT_HEIGHT / 2, (j)* SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
			}*/

			////Floor
			//scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("Wolf3DFloor_" + std::to_string(i) + "_" + std::to_string(j), SPOT_WIDTH, 0, SPOT_DEPTH, 1, 1, &floor, &shader));
			//scenes.at(currentScene)->getGameObject("Wolf3DFloor_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9(i * SPOT_WIDTH, 0, j * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));

			////Ceiling
			//scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("Wolf3DCeiling_" + std::to_string(i) + "_" + std::to_string(j), SPOT_WIDTH, 0, SPOT_DEPTH, 1, 1, &floor, &shader));
			//scenes.at(currentScene)->getGameObject("Wolf3DCeiling_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9(i * SPOT_WIDTH, SPOT_HEIGHT, j * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));

			////walls. Check if ajacent is a wall
			if (level.getPixel(i, j - 1).r == 0 && level.getPixel(i, j - 1).g == 0 && level.getPixel(i, j - 1).b == 0)
			{
				scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("Wolf3DWall_a_" + std::to_string(i) + "_" + std::to_string(j), SPOT_WIDTH, SPOT_HEIGHT, 0, 1, 1, &wall, &shader));
				scenes.at(currentScene)->getGameObject("Wolf3DWall_a_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9(i * SPOT_WIDTH, SPOT_HEIGHT/2, (j - 0.5) * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
			}
			if (level.getPixel(i, j + 1).r == 0 && level.getPixel(i, j + 1).g == 0 && level.getPixel(i, j + 1).b == 0)
			{
				scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("Wolf3DWall_b_" + std::to_string(i) + "_" + std::to_string(j), SPOT_WIDTH, SPOT_HEIGHT, 0, 1, 1, &wall, &shader));
				scenes.at(currentScene)->getGameObject("Wolf3DWall_b_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9(i * SPOT_WIDTH, SPOT_HEIGHT / 2, (j + 0.5) * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
			}
			if (level.getPixel(i - 1, j).r == 0 && level.getPixel(i - 1, j).g == 0 && level.getPixel(i - 1, j).b == 0)
			{
				scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("Wolf3DWall_c_" + std::to_string(i) + "_" + std::to_string(j), 0, SPOT_HEIGHT, SPOT_DEPTH, 1, 1, &wall, &shader));
				scenes.at(currentScene)->getGameObject("Wolf3DWall_c_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9((i - 0.5) * SPOT_WIDTH, SPOT_HEIGHT / 2, (j) * SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
			}
			if (level.getPixel(i + 1, j).r == 0 && level.getPixel(i + 1, j).g == 0 && level.getPixel(i + 1, j).b == 0)
			{
				scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("Wolf3DWall_d_" + std::to_string(i) + "_" + std::to_string(j), 0, SPOT_HEIGHT, SPOT_DEPTH, 1, 1, &wall, &shader));
				scenes.at(currentScene)->getGameObject("Wolf3DWall_d_" + std::to_string(i) + "_" + std::to_string(j))->setTransform(Vec9::createVec9((i + 0.5) * SPOT_WIDTH, SPOT_HEIGHT / 2, (j)* SPOT_DEPTH, 0, 0, 0, 1, 1, 1));
			}
		}
	}

	//scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("Wolf3DFloor", SPOT_WIDTH * level.getWidth(), 1, level.getHeight() * SPOT_DEPTH, 1, 1, &floor, &shader));
	//scenes.at(currentScene)->getGameObject("Wolf3DFloor")->setTransform(Vec9::createVec9(0, -5, 0, 0, 0, 0, 1, 1, 1));

	/*scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("Wolf3DWall", 5, 10, 5, 0.5, 0.5, &wall, &shader));
	scenes.at(currentScene)->getGameObject("Wolf3DWall")->move(Vec9::createVec9(Direction::MOVE_X, 10));*/

	//Wolf3d////////////////////////////////////
	
	//scenes.at(currentScene)->addGameObjectToScene(new GameObject("Ship", "./res/arwing.obj", &texture, &shader));
	//scenes.at(currentScene)->getGameObject("Ship")->move(Vec9::createVec9(Direction::MOVE_Y, 12));
	////scenes.at(currentScene)->addGameObjectToScene(new GameObject("Monkey", "./res/monkey3.obj", &texture2, &shader));

	//scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("TestCube", 5, 10, 5, 0.5, 0.5, &wall, &shader));
	//scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("TestCube2", 5, 10, 5, 1, 1, &wall, &shader));
	//scenes.at(currentScene)->getGameObject("TestCube2")->move(Vec9::createVec9(Direction::MOVE_X, 10));

	//scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("Floor", 25, 1, 25, 0.5, 0.5, &floor, &shader));
	//scenes.at(currentScene)->getGameObject("Floor")->move(Vec9::createVec9(Direction::MOVE_Y, -5));
	//scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("Ceiling", 25, 1, 25, 0.5, 0.5, &texture, &shader));
	//scenes.at(currentScene)->getGameObject("Ceiling")->move(Vec9::createVec9(Direction::MOVE_Y, 5));

	//scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("Wall1", 1, 10, 25, 0.5, 0.5, &wall, &shader));
	//scenes.at(currentScene)->getGameObject("Wall1")->move(Vec9::createVec9(Direction::MOVE_X, 12.5));
	//scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("Wall2", 1, 10, 25, 0.5, 0.5, &wall, &shader));
	//scenes.at(currentScene)->getGameObject("Wall2")->move(Vec9::createVec9(Direction::MOVE_X, -12.5));
	//scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("Wall3", 25, 10, 1, 0.5, 0.5, &wall, &shader));
	//scenes.at(currentScene)->getGameObject("Wall3")->move(Vec9::createVec9(Direction::MOVE_Z, 12.5));
	//scenes.at(currentScene)->addGameObjectToScene(GameObject::createCube("Wall4", 25, 10, 1, 0.5, 0.5, &wall, &shader));
	//scenes.at(currentScene)->getGameObject("Wall4")->move(Vec9::createVec9(Direction::MOVE_Z, -12.5));

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

	//scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_TRANSFORM, scenes.at(currentScene)->getGameObject("TestCube"), SDLK_f, Vec9::createVec9(Direction::ROT_Y, -0.01)));
	//scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_TRANSFORM, scenes.at(currentScene)->getGameObject("Ship"), SDLK_f, Vec9::createVec9(Direction::ROT_Y, -0.01)));
	

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

		shader.setPointLight(0, scenes.at(currentScene)->getCamera()->getPosition(), glm::fvec3(1, 1, 1), 10.0f, 20, 0, 0, 1);

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