#ifndef __AUDIOENGINE_H
#define __AUDIOENGINE_H

#include "AudioClip.h"
#include <vector>

class AudioEngine
{
public:
	AudioEngine();
	~AudioEngine();

	static AudioEngine* getAudioEngine();

	void loadAudioClip(std::string name, std::string filePath);

	AudioClip* getAudioClip(std::string name);

	/*void playAudioClip(std::string name);*/

private:
	static AudioEngine* s_instance;
	std::vector<AudioClip*> audioClips;

	SDL_AudioDeviceID device;
};

#endif