#include "../include/SDLWavAudioData.h"
#include <iostream>

SDLWavAudioData::SDLWavAudioData(const std::string& fileName, bool streamFromFile)
{
	SDL_AudioSpec wavSpec;
	Uint8* wavStart;
	Uint32 wavLength;

	//This is where its triggering
	if (SDL_LoadWAV(fileName.c_str(), &wavSpec, &wavStart, &wavLength) == NULL)
	{
		// TODO: Proper error handling
		std::cerr << "Failed\n";
		throw fileName;
	}

	m_pos = wavStart;
	m_start = wavStart;
	m_length = wavLength;
	m_totalLength = wavLength;
}

SDLWavAudioData::~SDLWavAudioData()
{
	SDL_FreeWAV(m_start);
}

size_t SDLWavAudioData::generateSamples(float* stream, size_t streamsLength, size_t pos, const SampleInfo& info)
{
	if (m_length == 0)
	{
		return (size_t)-1;
	}

	//m_pos = pos;
	//std::cout << *stream << " | " << m_length << " | " << (Uint32)streamsLength << " | " << pos << " | " << *(Sint16*)m_pos << " \n ";
	//Need to update m_pos based on pos's value
	if (pos == 0)
	{
		m_pos = m_start;
		m_length = m_totalLength;
	}

	Uint32 length = (Uint32)streamsLength;
	length = (length > m_length ? m_length : length);

	Sint16* samples = (Sint16*)m_pos;

	float factor =  (float)info.volume * 1.0f / 32768.0f;

	for (Uint32 i = 0; i < length; i++)
	{
		if (i >= streamsLength)
		{
			return (size_t)-1;
		}

		try
		{
			stream[i] = (*samples) * factor;
			samples++;
		}
		catch (const std::exception& e)
		{
			return (size_t)-1;
		}
	}

	m_pos = (Uint8*)samples;

	if ((int)m_length - (int)(length * 2) < 0)
	{
		//m_length = 0;
		m_length = m_totalLength;
		return (size_t)-1;
	}

	m_length -= (length * 2);

	return length;
}
size_t SDLWavAudioData::getAudioLength()
{
	return m_length;
}