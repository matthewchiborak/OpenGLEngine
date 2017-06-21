#include "../include/SDLAudioDevice.h"

//SDLAudioDevice::SDLAudioDevice()
//{
//}
//
//SDLAudioDevice::~SDLAudioDevice()
//{
//}

IAudioData* SDLAudioDevice::createAudioFromFile(const std::string& filePath)
{
	return new SDLWavAudioData(filePath, false);
}
void SDLAudioDevice::releaseAudio(IAudioData* audioData)
{
	if (audioData)
	{
		delete audioData;
	}
}