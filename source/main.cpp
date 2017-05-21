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
#include "../include/TextureManager.h"
#include "../include/ShaderManager.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv)
{
	Display display(WIDTH, HEIGHT, "Hello world!");

	int currentScene = 0;
	std::vector<Scene*> scenes;

	ShaderManager::getShaderManager()->loadShader("Phong", ".\\res\\PhongShader");
	ShaderManager::getShaderManager()->loadShader("Basic", ".\\res\\basicShader");

	ShaderManager::getShaderManager()->getShader("Phong")->setAmbientLight(glm::fvec3(0.1f,0.1f,0.1f));
	ShaderManager::getShaderManager()->getShader("Phong")->setBaseColor(glm::fvec3(1.0f, 1.0f, 1.0f));
	ShaderManager::getShaderManager()->getShader("Phong")->setDirectionalDirection(glm::fvec3(0, 1, 0));
	ShaderManager::getShaderManager()->getShader("Phong")->setDirectionalBase(glm::fvec3(0, 0, 0), 0);
	ShaderManager::getShaderManager()->getShader("Basic")->setAmbientLight(glm::fvec3(0.1f, 0.1f, 0.1f));
	ShaderManager::getShaderManager()->getShader("Basic")->setBaseColor(glm::fvec3(1.0f, 1.0f, 1.0f));
	ShaderManager::getShaderManager()->getShader("Basic")->setDirectionalDirection(glm::fvec3(0, 1, 0));
	ShaderManager::getShaderManager()->getShader("Basic")->setDirectionalBase(glm::fvec3(0, 0, 0), 0);
	//Note to self. Having directional color to white but intensity to 0 causes the specular reflection to give a flashlight effect

	ShaderManager::getShaderManager()->getShader("Phong")->setSpecularIntensity(2);
	ShaderManager::getShaderManager()->getShader("Phong")->setSpecularExponent(32);
	ShaderManager::getShaderManager()->getShader("Basic")->setSpecularIntensity(2);
	ShaderManager::getShaderManager()->getShader("Basic")->setSpecularExponent(32);

	/*shader.setPointLight(0, glm::fvec3(-2, 0, 6), glm::fvec3(1, 0, 0), 10.0f, 0, 0, 1);
	shader.setPointLight(1, glm::fvec3(2, 0, 7), glm::fvec3(0,0, 1), 10, 0, 0, 1);*/
	ShaderManager::getShaderManager()->getShader("Phong")->setPointLight(0, glm::fvec3(-2, 0, 6), glm::fvec3(1, 1, 1), 10.0f, 20, 0, 0, 1);
	ShaderManager::getShaderManager()->getShader("Basic")->setPointLight(0, glm::fvec3(-2, 0, 6), glm::fvec3(1, 1, 1), 10.0f, 20, 0, 0, 1);
	//shader.setPointLight(1, glm::fvec3(2, 0, 7), glm::fvec3(1, 1, 1), 10, 20, 0, 0, 1);

	//shader.setSpotLight(0, glm::fvec3(-2, 0, 6), glm::fvec3(1, 1, 1), 0.4f, 20, 0, 0, 0.02f, glm::vec3(0, 0, 1), 0.7);

	TextureManager::getTextureManager()->loadTexture("Wolf", ".\\res\\WolfCollection.png");
	TextureManager::getTextureManager()->loadTexture("SSWVA1", ".\\res\\SSWVA1.png");
	TextureManager::getTextureManager()->loadTexture("SSWVB1", ".\\res\\SSWVB1.png");
	TextureManager::getTextureManager()->loadTexture("SSWVC1", ".\\res\\SSWVC1.png");
	TextureManager::getTextureManager()->loadTexture("SSWVD1", ".\\res\\SSWVD1.png");
	TextureManager::getTextureManager()->loadTexture("SSWVE0", ".\\res\\SSWVE0.png");
	TextureManager::getTextureManager()->loadTexture("SSWVF0", ".\\res\\SSWVF0.png");
	TextureManager::getTextureManager()->loadTexture("SSWVG0", ".\\res\\SSWVG0.png");
	TextureManager::getTextureManager()->loadTexture("SSWVH0", ".\\res\\SSWVH0.png");
	TextureManager::getTextureManager()->loadTexture("SSWVI0", ".\\res\\SSWVI0.png");
	TextureManager::getTextureManager()->loadTexture("SSWVJ0", ".\\res\\SSWVJ0.png");
	TextureManager::getTextureManager()->loadTexture("SSWVK0", ".\\res\\SSWVK0.png");
	TextureManager::getTextureManager()->loadTexture("SSWVL0", ".\\res\\SSWVL0.png");
	TextureManager::getTextureManager()->loadTexture("SSWVM0", ".\\res\\SSWVM0.png");

	TextureManager::getTextureManager()->loadTexture("Gun0", ".\\res\\PISGB0.png");
	TextureManager::getTextureManager()->loadTexture("Gun1", ".\\res\\PISFA0.png");

	scenes.push_back(new Scene("Main", ".\\res\\Level1.png", WIDTH, HEIGHT));

	//Move the camera to start in the level
	scenes.at(currentScene)->resetCamera(Vec9::createVec9(17, 0.5, 17, 0, 0, 1, 0, 1, 0));
	//(Vec9::createVec9(0, 1, -5, 0, 0, 1, 0, 1, 0)

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

	scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_DOWN_DOOR_OPEN, scenes.at(currentScene)->getCamera(), SDLK_f, scenes.at(currentScene)->getDoors()));
	//scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_TRANSFORM, scenes.at(currentScene)->getGameObject("TestCube"), SDLK_f, Vec9::createVec9(Direction::ROT_Y, -0.01)));
	//scenes.at(currentScene)->addInputToScene(new Input(KEY_PRESS_TRANSFORM, scenes.at(currentScene)->getGameObject("Ship"), SDLK_f, Vec9::createVec9(Direction::ROT_Y, -0.01)));
	scenes.at(currentScene)->addInputToScene(new Input(LEFT_CLICK_DOWN_SHOOT, scenes.at(currentScene)->getCamera(), scenes.at(currentScene)->getMonsters()));

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
		display.clear(0.0f, 0.0f, 1.0f, 0.0f);

		ShaderManager::getShaderManager()->getShader("Phong")->setPointLight(0, scenes.at(currentScene)->getCamera()->getPosition(), glm::fvec3(1, 1, 1), 10.0f, 20, 0, 0, 1);

		scenes.at(currentScene)->update(&display);
		display.Update();

		counter += 0.01f;
		frames++;

		//Output the framerate
		if (frameCounter >= Time::SECOND)
		{
			std::cout << "FPS: " << frames << "   HP:"  << scenes.at(currentScene)->getCamera()->getHealth() << "\n";
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