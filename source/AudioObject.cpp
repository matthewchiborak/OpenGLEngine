#include "../include/AudioObject.h"

AudioObject::AudioObject(const SampleInfo& info, IAudioData* data)
{
	this->m_audioPos = 0;
	this->m_audioLength = data->getAudioLength();
	this->m_sampleInfo = info;
	this->m_audioData = data;
}

AudioObject::~AudioObject()
{
}

bool AudioObject::generateSamples(float* stream, size_t streamLength)
{
	m_audioPos = m_audioData->generateSamples(stream, streamLength, m_audioPos, m_sampleInfo);

	if (m_audioPos == (size_t)-1)
	{
		//Reached the end
		m_audioPos = 0;
		return false;
	}

	return true;
}

void AudioObject::setPos(double pos)
{
	if (pos < 0)
	{
		pos = 0;
	}
	else if (pos > 1)
	{
		pos = 1;
	}

	m_audioPos = posToAbsolutePos(pos);
}

size_t AudioObject::posToAbsolutePos(double pos)
{
	//Convert normalize value to the pos in the audio file
	return (size_t)(pos * m_audioLength);
}