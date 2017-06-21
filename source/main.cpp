#include <iostream>
#include <GL/glew.h>
#include <D:/OpenGL2017/SDL2-devel-2.0.5-VC/SDL2-2.0.5/include/SDL.h>

#include "../include/CoreEngine.h"
#include "../include/TestScene.h"

#define WIDTH 800
#define HEIGHT 600

//TEST CODE
#define FILE_PATH ".\\res\\testClip.wav"
//#include "iaudiodevice.hpp"
//#include "iaudiocontext.hpp"
//#include "audioobject.hpp"
#include "../include/IAudioDevice.h"
#include "../include/IAudioContext.h"
#include "../include/AudioObject.h"
#include "../include/SDLAudioDevice.h"
#include "../include/SDLAudioContext.h"
#include "../include/SampleInfo.h"

int main(int argc, char** argv)
{
	//TEST CODE
	SDL_Init(SDL_INIT_AUDIO);
	IAudioDevice* device = new SDLAudioDevice();
	IAudioContext* context = new SDLAudioContext();

	IAudioData* data = device->createAudioFromFile(FILE_PATH);

	SampleInfo info;
	info.volume = 1.0;

	AudioObject sound(info, data);

	char in = 0;
	while (in != 'q')
	{
		std::cin >> in;
		switch (in)
		{
		case 'a':
			context->playAudio(sound);
			break;
		case 's':
			context->pauseAudio(sound);
			break;
		case 'd':
			context->stopAudio(sound);
			break;
		}
	}

	device->releaseAudio(data);
	delete context;
	delete device;

	//TEST CODE

	CoreEngine::getCoreEngine()->init(WIDTH, HEIGHT, 30, "Hello world!!!");

	TextureManager::getTextureManager()->loadTexture("Arwing", ".\\res\\body.png");

	MeshManager::getMeshManager()->loadMesh("Arwing", ".\\res\\arwing.obj");

	//AudioEngine::getAudioEngine()->loadAudioClip("SCM", ".\\res\\SweetChinMusic.mp3");

	Scene* testScene = new TestScene();
	CoreEngine::getCoreEngine()->loadScene(testScene, "Test", "Test");

	CoreEngine::getCoreEngine()->run();
	
	return 0;
}