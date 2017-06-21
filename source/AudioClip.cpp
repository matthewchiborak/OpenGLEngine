#include "../include/AudioClip.h"

AudioClip::AudioClip(std::string name, std::string filePath)
{
	this->name = name;

	if (SDL_LoadWAV(filePath.c_str(), &wavSpec, &wavStart, &wavLength) == NULL)
	{
		std::cerr << "Error with Audio Filepath: " << filePath << "\n";
	}

	//SDL_AudioDeviceID 
	localDevice = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

	if (localDevice == 0)
	{
		//Failed
		std::cerr << "Error could not find audio device" << SDL_GetError() << "\n";
	}

	//Set up the callback function
	//wavSpec.callback = audioCallBack;
	wavSpec.userdata = &localDevice;

	//SDL_CloseAudioDevice(localDevice);
}

AudioClip::~AudioClip()
{
	//Free the memory
	SDL_FreeWAV(wavStart);
	SDL_CloseAudioDevice(localDevice);
}

//void AudioClip::play()
//{
//	SDL_AudioDeviceID localDevice = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);
//
//	if (localDevice == 0)
//	{
//		//Failed
//		std::cerr << "Error could not find audio device" << SDL_GetError() << "\n";
//	}
//
//	//wavSpec.cal
//
//	SDL_CloseAudioDevice(localDevice);
//}

std::string AudioClip::getName()
{
	return name;
}

void AudioClip::audioCallBack(void* userdata, Uint8* stream, int streamLength)
{
	AudioData* audio = (AudioData*)userdata;

	if (audio->length == 0)
	{
		return;
	}

	Uint32 length = (Uint32)streamLength;
	length = (length > audio->length ? audio->length : length);

	SDL_memcpy(stream, audio->pos, length);

	audio->pos += length;
	audio->length -= length;
}

Uint8* AudioClip::getWavStart()
{
	return wavStart;
}
Uint32 AudioClip::getWavLength()
{
	return wavLength;
}