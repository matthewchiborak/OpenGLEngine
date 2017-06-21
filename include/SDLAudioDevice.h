#ifndef __SDLAUDIODEVICE_H
#define __SDLAUDIODEVICE_H

#include "IAudioDevice.h"
#include "SDLWavAudioData.h"

class SDLAudioDevice : public IAudioDevice
{
public:
	//SDLAudioDevice();
	//~SDLAudioDevice();

	virtual IAudioData* createAudioFromFile(const std::string& filePath);
	virtual void releaseAudio(IAudioData* audioData);

private:

};

#endif