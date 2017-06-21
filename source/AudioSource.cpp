#include "../include/AudioSource.h"

AudioSource::AudioSource()
{
	audioClip = NULL;
}

AudioSource::~AudioSource()
{
}

void AudioSource::play()
{
	if (audioClip == NULL)
	{
		return;
	}

	//SDL_PauseAudioDevice(audioClip)
}

void AudioSource::setAudioClip(AudioClip* audioClip)
{
	this->audioClip = audioClip;
	audioData.pos = audioClip->getWavStart();
	audioData.length = audioClip->getWavLength();
}