#include "../include/AudioEngine.h"

AudioEngine* AudioEngine::s_instance = 0;

AudioEngine::AudioEngine()
{
	
}

AudioEngine::~AudioEngine()
{
	
}

AudioEngine* AudioEngine::getAudioEngine()
{
	if (!s_instance)
	{
		s_instance = new AudioEngine();
	}

	return s_instance;
}

void AudioEngine::loadAudioClip(std::string name, std::string filePath)
{
	audioClips.push_back(new AudioClip(name, filePath));
}

AudioClip* AudioEngine::getAudioClip(std::string name)
{
	for (int i = 0; i < audioClips.size(); i++)
	{
		if (audioClips.at(i)->getName() == name)
		{
			return audioClips.at(i);
		}
	}
}

//void AudioEngine::playAudioClip(std::string name)
//{
//	for (int i = 0; i < audioClips.size(); i++)
//	{
//		if (audioClips.at(i)->getName() == name)
//		{
//			audioClips.at(i)->play();
//			break;
//		}
//	}
//}