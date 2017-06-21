#ifndef __AUDIOSOURCE_H
#define __AUDIOSOURCE_H

#include "AudioClip.h"

class AudioSource
{
public:
	AudioSource();
	~AudioSource();

	void play();
	void setAudioClip(AudioClip* audioClip);

private:
	AudioData audioData;
	AudioClip* audioClip;

	SDL_AudioDeviceID localDevice;
};

#endif