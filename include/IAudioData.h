#ifndef __IAUDIODATA_H
#define __IAUDIODATA_H

#include "SampleInfo.h"
#include <cstddef>

class IAudioData
{
public:
	//IAudioData();
	virtual ~IAudioData() {}
	virtual size_t generateSamples(float* stream, size_t streamsLength, size_t pos, const SampleInfo& info) = 0;
	virtual size_t getAudioLength() = 0;

private:

};

#endif