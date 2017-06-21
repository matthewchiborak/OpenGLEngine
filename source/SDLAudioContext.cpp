#include "../include/SDLAudioContext.h"

static void SDLAudioContext_AudioCallback(void* userData, Uint8* streamIn, int length)
{
	SDLAudioContext* context = (SDLAudioContext*)userData;
	context->generateSamples(streamIn, length);
}

SDLAudioContext::SDLAudioContext()
{
	SDL_AudioSpec spec;

	SDL_zero(spec);
	//TODO Get rid of hardcode
	spec.freq = 44100;
	//Set to 16 bit and either big or little indian depending on the computer
	spec.format = AUDIO_S16SYS;
	spec.channels = 2; //Sterio
	spec.samples = 2048;
	spec.callback = SDLAudioContext_AudioCallback;
	spec.userdata = this;

	//SDL_AudioDeviceID 
	//m_device = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);
	m_device = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);
	if (m_device == 0)
	{
		// TODO: Proper error handling
		//std::cerr << "Error: " << SDL_GetError() << std::endl;
		throw SDL_GetError();
		//return 1;
	}

	SDL_PauseAudioDevice(m_device, 0);
}

SDLAudioContext::~SDLAudioContext()
{
	SDL_CloseAudioDevice(m_device);
}

void SDLAudioContext::playAudio(AudioObject& ao)
{
	//Get the mutex
	SDL_LockAudioDevice(m_device);

	//Remove it if it already exists so not playing 2 at same time
	removeAudio(ao);
	m_playingAudio.push_back(&ao);

	//Release the mutex
	SDL_UnlockAudioDevice(m_device);
}
void SDLAudioContext::pauseAudio(AudioObject& ao)
{
	//Get the mutex
	SDL_LockAudioDevice(m_device);

	//Remove it
	removeAudio(ao);

	//Release the mutex
	SDL_UnlockAudioDevice(m_device);
}
void SDLAudioContext::stopAudio(AudioObject& ao)
{
	//Get the mutex
	SDL_LockAudioDevice(m_device);

	//Remove it and set its pos back to the beginning
	if (removeAudio(ao))
	{
		ao.setPos(0);
	}

	//Release the mutex
	SDL_UnlockAudioDevice(m_device);
}

void SDLAudioContext::generateSamples(Uint8* streamIn, int streamInLength)
{
	//The actual size. The parameters are in bytes, not sample, so need to fix this
	size_t streamLength = (size_t)(streamInLength / 2);

	m_stream.reserve(streamLength);
	float* floatStream = *(float**)(&m_stream);

	for (size_t i = 0; i < streamLength; i++)
	{
		floatStream[i] = 0;
	}

	std::vector<AudioObject*>::iterator it = m_playingAudio.begin();
	std::vector<AudioObject*>::iterator end = m_playingAudio.end();
	for (; it != end; ++it)
	{
		if (!(*it)->generateSamples(floatStream, streamLength))
		{
			//If generation failed, remove it
			removeAudio(*(*it));
		}
	}

	Sint16* stream = (Sint16*)streamIn;
	for (size_t i = 0; i < streamLength; i++)
	{
		float val = floatStream[i];

		if (val > 1)
		{
			val = 1;
		}
		else if (val < -1)
		{
			val = -1;
		}

		stream[i] = (Sint16)(val * 32767);
	}
}

bool SDLAudioContext::removeAudio(AudioObject& ao)
{
	std::vector<AudioObject*>::iterator it = m_playingAudio.begin();
	std::vector<AudioObject*>::iterator end = m_playingAudio.end();

	for (; it != end; ++it)
	{
		if (*it == &ao)
		{
			m_playingAudio.erase(it);
			return true;
		}
	}
	return false;
}