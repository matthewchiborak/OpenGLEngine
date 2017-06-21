#ifndef __SDLAUDIOCONTEXT_H
#define __SDLAUDIOCONTEXT_H

#include "IAudioContext.h"
#include <vector>
#include <iostream>
#include <D:/OpenGL2017/SDL2-devel-2.0.5-VC/SDL2-2.0.5/include/SDL.h>

class SDLAudioContext : public IAudioContext
{
public:
	SDLAudioContext();
	virtual ~SDLAudioContext();
	virtual void playAudio(AudioObject& ao);
	virtual void pauseAudio(AudioObject& ao);
	virtual void stopAudio(AudioObject& ao);

	void generateSamples(Uint8* streamIn, int streamInLength);
private:
	//Audio device taht is used to play the audio
	SDL_AudioDeviceID m_device;
	std::vector<float> m_stream;
	std::vector<AudioObject*> m_playingAudio;

	bool removeAudio(AudioObject& ao);

	SDLAudioContext(SDLAudioContext& other) { (void)other; }
	void operator=(const SDLAudioContext& other) { (void)other; }
};

#endif