#ifndef __SDLWAVAUDIODATA_H
#define __SDLWAVAUDIODATA_H

#include "IAudioData.h"
#include <D:/OpenGL2017/SDL2-devel-2.0.5-VC/SDL2-2.0.5/include/SDL.h>
#include <string>

class SDLWavAudioData : public IAudioData
{
public:
	SDLWavAudioData(const std::string& fileName, bool streamFromFile);
	virtual ~SDLWavAudioData();

	virtual size_t generateSamples(float* stream, size_t streamsLength, size_t pos, const SampleInfo& info);
	virtual size_t getAudioLength();

private:
	Uint8* m_pos;
	Uint8* m_start;
	Uint32 m_length;

	SDLWavAudioData(SDLWavAudioData& other) { (void)other; }
	void operator=(const SDLWavAudioData& other) { (void)other; }
};

#endif