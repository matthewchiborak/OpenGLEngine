#ifndef __AUDIOCLIP_H
#define __AUDIOCLIP_H

#include <D:/OpenGL2017/SDL2-devel-2.0.5-VC/SDL2-2.0.5/include/SDL.h>
#include <string>
#include <iostream>

struct AudioData
{
	Uint8* pos;
	Uint32 length;
};

class AudioClip
{
public:
	AudioClip(std::string name, std::string filePath);
	~AudioClip();

	//TODO Might be a good idea to add parameter that starts audio clip from part way in a clip
	//void play();

	std::string getName();
	Uint8* getWavStart();
	Uint32 getWavLength();

	void audioCallBack(void* userdata, Uint8* stream, int streamLength);


private:
	std::string name;

	//Info needed for the audio file
	//Frequency and channel info
	SDL_AudioSpec wavSpec;
	//Begining of the wave file
	Uint8* wavStart;
	//Length of the wav file
	Uint32 wavLength;

	SDL_AudioDeviceID localDevice;
};

#endif