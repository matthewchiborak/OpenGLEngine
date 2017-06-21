#ifndef __IAUDIODEVICE_H
#define __IAUDIODEVICE_H

#include <string>
#include "IAudioData.h"

class IAudioDevice
{
public:
	//IAudioDevice();
	virtual ~IAudioDevice() {}
	virtual IAudioData* createAudioFromFile(const std::string& filePath) = 0;
	virtual void releaseAudio(IAudioData* audioData) = 0;

private:

};

#endif