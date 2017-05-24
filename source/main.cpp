#include <iostream>
#include <GL/glew.h>
#include <D:/OpenGL2017/SDL2-devel-2.0.5-VC/SDL2-2.0.5/include/SDL.h>

#include "../include/CoreEngine.h"
#include "../include/TestScene.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv)
{
	//Game or scene? Should change it so the game has scenes???
	Game testGame;
	CoreEngine::getCoreEngine()->init(WIDTH, HEIGHT, 30, &testGame, "Hello world!!!");

	ShaderManager::getShaderManager()->loadShader("Phong", ".\\res\\PhongShader");
	ShaderManager::getShaderManager()->loadShader("Basic", ".\\res\\basicShader");

	ShaderManager::getShaderManager()->getShader("Phong")->setAmbientLight(glm::fvec3(0.1f,0.1f,0.1f));
	ShaderManager::getShaderManager()->getShader("Phong")->setBaseColor(glm::fvec3(1.0f, 1.0f, 1.0f));
	ShaderManager::getShaderManager()->getShader("Phong")->setDirectionalDirection(glm::fvec3(0, 1, 0));
	ShaderManager::getShaderManager()->getShader("Phong")->setDirectionalBase(glm::fvec3(1, 1, 1), 1);
	ShaderManager::getShaderManager()->getShader("Basic")->setAmbientLight(glm::fvec3(0.1f, 0.1f, 0.1f));
	ShaderManager::getShaderManager()->getShader("Basic")->setBaseColor(glm::fvec3(1.0f, 1.0f, 1.0f));
	ShaderManager::getShaderManager()->getShader("Basic")->setDirectionalDirection(glm::fvec3(0, 1, 0));
	ShaderManager::getShaderManager()->getShader("Basic")->setDirectionalBase(glm::fvec3(1, 1, 1), 1);
	//Note to self. Having directional color to white but intensity to 0 causes the specular reflection to give a flashlight effect

	ShaderManager::getShaderManager()->getShader("Phong")->setSpecularIntensity(2);
	ShaderManager::getShaderManager()->getShader("Phong")->setSpecularExponent(32);
	ShaderManager::getShaderManager()->getShader("Basic")->setSpecularIntensity(2);
	ShaderManager::getShaderManager()->getShader("Basic")->setSpecularExponent(32);

	ShaderManager::getShaderManager()->getShader("Phong")->setPointLight(0, glm::fvec3(0, 0, 0), glm::fvec3(1, 1, 1), 10.0f, 20, 0, 0, 1);
	ShaderManager::getShaderManager()->getShader("Basic")->setPointLight(0, glm::fvec3(17, 0.5, 13), glm::fvec3(1, 1, 1), 10.0f, 20, 0, 0, 1);

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

	TextureManager::getTextureManager()->loadTexture("Medkit", ".\\res\\MEDIA0.png");

	TextureManager::getTextureManager()->loadTexture("Arwing", ".\\res\\body.png");

	
	Scene* testScene = new TestScene();
	CoreEngine::getCoreEngine()->loadScene(testScene, "Test", "Test");

	CoreEngine::getCoreEngine()->run();
	
	return 0;
}