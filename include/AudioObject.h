#ifndef __AUDIOOBJECT_H
#define __AUDIOOBJECT_H

#include "IAudioData.h"
#include "SampleInfo.h"

class AudioObject
{
public:
	AudioObject(const SampleInfo& info, IAudioData* data);
	~AudioObject();

	//Returns true is still more audio, false if readed the end
	bool generateSamples(float* stream, size_t streamLength);
	//Between 0 and 1
	void setPos(double pos);

private:
	size_t m_audioPos;
	size_t m_audioLength;
	SampleInfo m_sampleInfo;
	IAudioData* m_audioData;

	size_t posToAbsolutePos(double pos);
};

#endif